# Files brought in from Codec2 that are mandatory for LPCNet.
set(codec2_import_srcs
    from_codec2/sine.c
    from_codec2/nlp.c
    from_codec2/codec2_fft.c
    from_codec2/kiss_fft.c
    from_codec2/kiss_fftr.c
)

# Set visibility of files brought in from Codec2 so that they're not visible to 
# users (such as Codec2 itself).
foreach(CODEC2_FILE IN LISTS codec2_import_srcs)
    set_source_files_properties(${CODEC2_FILE} PROPERTIES COMPILE_FLAGS "-fvisibility=hidden -include ${CMAKE_CURRENT_SOURCE_DIR}/from_codec2/codec2_renames.h")
endforeach()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
    ${lpcnet_SOURCE_DIR})

set(lpcnet_freedv_srcs
    freq.c
    kiss_fft.c
    celt_lpc.c
    pitch.c
    codec2_pitch.c
    mbest.c
    lpcnet_quant.c
    lpcnet_dump.c
    4stage_pred_vq.c
    4stage_direct_split_vq.c
    4stage_direct_split_indopt_vq.c
    lpcnet.c
    lpcnet_freedv.c
    nnet.c
    ${lpcnet_SOURCE_DIR}/nnet_data.c
)

if(LPCNET_C_PROC_FLAGS)
foreach(LPCNET_FILE IN LISTS lpcnet_freedv_srcs)
    set_source_files_properties(${LPCNET_FILE} PROPERTIES COMPILE_FLAGS ${LPCNET_C_PROC_FLAGS})
endforeach()
endif(LPCNET_C_PROC_FLAGS)

add_library(lpcnetfreedv SHARED ${lpcnet_freedv_srcs} ${codec2_import_srcs})

set_target_properties(lpcnetfreedv PROPERTIES
    PUBLIC_HEADER lpcnet_freedv.h
	VERSION ${LPCNET_VERSION}
	SOVERSION ${LPCNET_SOVERSION}
)
target_include_directories(lpcnetfreedv INTERFACE
    $<INSTALL_INTERFACE:include/lpcnet>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
install(TARGETS lpcnetfreedv EXPORT lpcnetfreedv-config
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT lib
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT lib
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/lpcnet COMPONENT dev
)

install(EXPORT lpcnetfreedv-config
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/lpcnetfreedv COMPONENT dev
)
# Export libfreedv target for import into codec2 from build tree.
export(TARGETS lpcnetfreedv
    FILE ${CMAKE_BINARY_DIR}/lpcnetfreedv.cmake
)

add_executable(dump_data dump_data.c)
target_link_libraries(dump_data lpcnetfreedv m)

add_executable(test_lpcnet test_lpcnet.c nnet_rw.c)
target_link_libraries(test_lpcnet lpcnetfreedv m)

if(
    (${SSE} AND (${SSE_PRESENT} OR ${SSE_PRESENT} GREATER 0)) OR
    (${AVX} AND (${AVX_PRESENT} OR ${AVX_PRESENT} GREATER 0)) OR
    (${AVX2} AND (${AVX2_PRESENT} OR ${AVX2_PRESENT} GREATER 0)) OR
    (${NEON} AND (${NEON_PRESENT} OR ${NEON_PRESENT} GREATER 0)) OR
    CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
    add_executable(test_vec test_vec.c)
    target_link_libraries(test_vec m)
    
    if(LPCNET_C_PROC_FLAGS)
        set_source_files_properties(test_vec.c PROPERTIES COMPILE_FLAGS ${LPCNET_C_PROC_FLAGS})
    endif(LPCNET_C_PROC_FLAGS)
else()
    message(WARNING "No SSE/AVX/AVX2 CPU flags identified, not building test_vec.")
endif()

add_executable(quant_feat quant_feat.c)
target_link_libraries(quant_feat lpcnetfreedv m)

add_executable(tcodec2_pitch tcodec2_pitch.c)
target_link_libraries(tcodec2_pitch lpcnetfreedv m)

add_executable(weight weight.c)
target_link_libraries(weight m)

add_executable(tdump tdump.c)
target_link_libraries(tdump lpcnetfreedv m)

add_executable(quant_test quant_test.c)
target_link_libraries(quant_test lpcnetfreedv m)

add_executable(quant2c quant2c.c)
target_link_libraries(quant2c m)

add_executable(diff32 diff32.c)
target_link_libraries(diff32 m)

add_executable(ramp ramp.c)
target_link_libraries(ramp m)

add_executable(quant_enc quant_enc.c)
target_link_libraries(quant_enc lpcnetfreedv m)

add_executable(quant_dec quant_dec.c)
target_link_libraries(quant_dec lpcnetfreedv m)

add_executable(lpcnet_enc lpcnet_enc.c)
target_link_libraries(lpcnet_enc lpcnetfreedv m)

add_executable(lpcnet_dec lpcnet_dec.c nnet_rw.c)
target_link_libraries(lpcnet_dec lpcnetfreedv m)

add_executable(idct idct.c)
target_link_libraries(idct lpcnetfreedv m)

add_executable(nnet2f32 nnet2f32.c nnet_rw.c)
target_link_libraries(nnet2f32 lpcnetfreedv m)

add_executable(sw2packedulaw sw2packedulaw.c)
target_link_libraries(sw2packedulaw lpcnetfreedv m)

add_executable(thash thash.c)
target_link_libraries(thash lpcnetfreedv m)

install(TARGETS lpcnet_enc lpcnet_dec
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT tools
    )
