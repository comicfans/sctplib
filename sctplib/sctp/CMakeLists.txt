
include_directories(${PROJECT_SOURCE_DIR}/3rd/glib/include/glib-2.0)
include_directories(${PROJECT_SOURCE_DIR}/3rd/glib/lib/glib-2.0/include)



add_library(sctp 
    adaptation.c	
	auxiliary.c	
	chunkHandler.c	
	distribution.c	
	errorhandler.c
	flowcontrol.c	
	globals.c	
	md5.c	
	pathmanagement.c	
	rbundling.c	
	recvctrl.c	
	reltransfer.c	
	sbundling.c	
	SCTP-control.c	
	streamengine.c	
	timer_list.c
    )

target_link_libraries(sctp ${GLIB_LIB} ws2_32)
