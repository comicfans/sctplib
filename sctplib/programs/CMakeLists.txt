

foreach( src 
	combined_server 
	echo_tool  
        daytime_server  
        discard_server   
        echo_server   
        chargen_server  
        terminal)

    add_executable(${src} ${src}.c sctp_wrapper.c)

    target_link_libraries(${src} sctp)



endforeach()

