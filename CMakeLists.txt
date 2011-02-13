PROJECT(cppcheck)
find_package(KDE4 REQUIRED)
find_package(KDevPlatform REQUIRED)

ADD_DEFINITIONS(-Wall -Wextra)

add_subdirectory(icons)

include_directories(
    ${KDEVPLATFORM_INCLUDE_DIR}
    ${KDE4_INCLUDES}
)

set(kdevcppcheck_SRCS
    ccppcheckfactory.cpp
    cppcheckplugin.cpp
)

kde4_add_plugin(kdevcppcheck ${kdevcppcheck_SRCS})

target_link_libraries(kdevcppcheck
    ${KDEVPLATFORM_UTIL_LIBRARIES}
    ${KDEVPLATFORM_INTERFACES_LIBRARIES}
    ${KDEVPLATFORM_PROJECT_LIBRARIES}
)

########### install files ###############
install(TARGETS kdevcppcheck         DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES   kdevcppcheck.desktop DESTINATION ${SERVICES_INSTALL_DIR})
