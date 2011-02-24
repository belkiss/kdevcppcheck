PROJECT(cppcheck)
FIND_PACKAGE(KDE4 REQUIRED)
FIND_PACKAGE(KDevPlatform REQUIRED)
FIND_PACKAGE(PCRE REQUIRED)

# see full compilation lines
SET(CMAKE_VERBOSE_MAKEFILE 1)

################################################################################
# GET THE CPPCHECK ORIGINAL RELEASE (VENDOR)
SET(CPPCHECK_SRC "${CMAKE_BINARY_DIR}/externals/cppcheck")

INCLUDE(ExternalProject)
ExternalProject_Add(
    cppcheck-1-47                # Name for custom target
    # [DEPENDS projects...]       # Targets on which the project depends
    # [PREFIX dir]                # Root dir for entire project
    # [LIST_SEPARATOR sep]        # Sep to be replaced by ; in cmd lines
    # [TMP_DIR dir]               # Directory to store temporary files
    # [STAMP_DIR dir]             # Directory to store step timestamps
    #--Download step--------------
    # [DOWNLOAD_DIR dir]          # Directory to store downloaded files
    # [DOWNLOAD_COMMAND cmd...]   # Command to download source tree
    # [CVS_REPOSITORY cvsroot]    # CVSROOT of CVS repository
    # [CVS_MODULE mod]            # Module to checkout from CVS repo
    # [CVS_TAG tag]               # Tag to checkout from CVS repo
    # [SVN_REPOSITORY url]        # URL of Subversion repo
    # [SVN_REVISION rev]          # Revision to checkout from Subversion repo
    # [SVN_USERNAME john ]        # Username for Subversion checkout and update
    # [SVN_PASSWORD doe ]         # Password for Subversion checkout and update
    # GIT_REPOSITORY git://github.com/danmar/cppcheck.git # URL of git repo
    # GIT_TAG        1.47 # Git branch name, commit id or tag
    URL http://downloads.sourceforge.net/cppcheck/cppcheck-1.47.tar.bz2 # Full path or URL of source
    URL_MD5 e33263a34fdd9f3f3eeadbe3008fd498 # MD5 checksum of file at URL
    # [TIMEOUT seconds]           # Time allowed for file download operations
    #--Update/Patch step----------
    # [UPDATE_COMMAND cmd...]     # Source work-tree update command
    # [PATCH_COMMAND cmd...]      # Command to patch downloaded source
    #--Configure step-------------
    SOURCE_DIR ${CPPCHECK_SRC}    # Source dir to be used for build
    CONFIGURE_COMMAND ""          # Build tree configuration command
    # [CMAKE_COMMAND /.../cmake]  # Specify alternative cmake executable
    # [CMAKE_GENERATOR gen]       # Specify generator for native build
    # [CMAKE_ARGS args...]        # Arguments to CMake command line
    # [CMAKE_CACHE_ARGS args...]  # Initial cache arguments, of the form -Dvar:string=on
    #--Build step-----------------
    # [BINARY_DIR dir]            # Specify build dir location
    BUILD_COMMAND ""              # Command to drive the native build
    BUILD_IN_SOURCE 1             # Use source dir for build dir
    #--Install step---------------
    # [INSTALL_DIR dir]           # Installation prefix
    INSTALL_COMMAND ""            # Command to drive install after build
    #--Test step------------------
    # [TEST_BEFORE_INSTALL 1]     # Add test step executed before install step
    # [TEST_AFTER_INSTALL 1]      # Add test step executed after install step
    # [TEST_COMMAND cmd...]       # Command to drive test
    #--Output logging-------------
    LOG_DOWNLOAD 1                # Wrap download in script to log output
    LOG_UPDATE 1                  # Wrap update in script to log output
    LOG_CONFIGURE 1               # Wrap configure in script to log output
    LOG_BUILD 1                   # Wrap build in script to log output
    LOG_TEST 1                    # Wrap test in script to log output
    LOG_INSTALL 1                 # Wrap install in script to log output
    #--Custom targets-------------
    # [STEP_TARGETS st1 st2 ...]  # Generate custom targets for these steps
)
################################################################################

ADD_DEFINITIONS(-Wall -Wextra -fexceptions)

ADD_SUBDIRECTORY(icons)

INCLUDE_DIRECTORIES(
    ${CPPCHECK_SRC}/lib
    ${KDEVPLATFORM_INCLUDE_DIR}
    ${KDE4_INCLUDES}
)

SET(vendor_cppcheck_SRCS
    ${CPPCHECK_SRC}/lib/checkunusedfunctions.cpp
    ${CPPCHECK_SRC}/lib/timer.cpp
    ${CPPCHECK_SRC}/lib/settings.cpp
    ${CPPCHECK_SRC}/lib/preprocessor.cpp
    ${CPPCHECK_SRC}/lib/symboldatabase.cpp
    ${CPPCHECK_SRC}/lib/mathlib.cpp
    ${CPPCHECK_SRC}/lib/path.cpp
    ${CPPCHECK_SRC}/lib/errorlogger.cpp
    ${CPPCHECK_SRC}/lib/token.cpp
    ${CPPCHECK_SRC}/lib/tokenize.cpp
    ${CPPCHECK_SRC}/lib/cppcheck.cpp
)
# tell cmake the files might be missing (they aren't downloaded yet)
SET_SOURCE_FILES_PROPERTIES(${vendor_cppcheck_SRCS} PROPERTIES
                            GENERATED 1)


SET(kdevcppcheck_SRCS
    ccppcheckexecutor.cpp
    ccppcheckwidget.cpp
    ccppcheckfactory.cpp
    cppcheckplugin.cpp
)

KDE4_ADD_PLUGIN(kdevcppcheck
                ${vendor_cppcheck_SRCS}
                ${kdevcppcheck_SRCS})

TARGET_LINK_LIBRARIES(kdevcppcheck
    ${PCRE_LIBRARIES}
    ${KDEVPLATFORM_UTIL_LIBRARIES}
    ${KDEVPLATFORM_INTERFACES_LIBRARIES}
    ${KDEVPLATFORM_PROJECT_LIBRARIES}
)

########### install files ###############
INSTALL(TARGETS kdevcppcheck         DESTINATION ${PLUGIN_INSTALL_DIR})
INSTALL(FILES   kdevcppcheck.desktop DESTINATION ${SERVICES_INSTALL_DIR})
