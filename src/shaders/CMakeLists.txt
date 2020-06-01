file(GLOB vertShads "*.vert")
foreach(vertShad ${vertShads})
	get_filename_component(vertFile ${vertShad} NAME)
	configure_file(${CMAKE_SOURCE_DIR}/src/shaders/${vertFile}
				   ${CMAKE_SOURCE_DIR}/bin/${vertFile}
				   COPYONLY)
endforeach()

file(GLOB fragShads "*.frag")
foreach(fragShad ${fragShads})
	get_filename_component(fragFile ${fragShad} NAME)
	configure_file(${CMAKE_SOURCE_DIR}/src/shaders/${fragFile}
				   ${CMAKE_SOURCE_DIR}/bin/${fragFile}
				   COPYONLY)
endforeach()
