
SET(RCS_HIGHGUI_SRCS
HighGuiWindow.cpp
HighGuiPlot.cpp
HighGuiLabel.cpp
HighGuiImage.cpp
HighGuiButton.cpp
HighGuiWidget.cpp
HighGui.cpp
HighGuiSlider.cpp
)

SET(RCS_GUI_SRCS
ControllerWidgetBase.cpp
ForceControlGui.cpp
GuiFactory.cpp
JointSlider.cpp
JointWidget.cpp
LcdSlider.cpp
MatNdWidget.cpp
PPSGui.cpp
PPSWidget.cpp
Rcs_guiFactory.c
SimpleSlider.cpp
Slider1Dof.cpp
SliderCheck1Dof.cpp
TaskWidget.cpp
DblSlider.cpp
${RCS_HIGHGUI_SRCS}
)

IF(WIN32)
  SET_SOURCE_FILES_PROPERTIES( ${RCS_GUI_SRCS} PROPERTIES LANGUAGE CXX )
  
  IF(CREATE_WIN_DLL)
    ADD_DEFINITIONS(-DRCSGUI_EXPORTS)
  ENDIF(CREATE_WIN_DLL)

ENDIF()

SET(RCS_HIGHGUI_HEADERS
HighGuiLabel.h
HighGuiSlider.h
HighGuiButton.h
HighGuiWindow.h
HighGuiPlot.h
HighGuiWidget.h
)

FIND_PACKAGE(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

ADD_LIBRARY(RcsGui ${LIBRARY_LINKING_TYPE} ${RCS_GUI_SRCS} )
TARGET_LINK_LIBRARIES(RcsGui RcsCore Qt5::Core Qt5::Gui Qt5::Widgets ${QWT_LIBRARIES})
SET_TARGET_PROPERTIES(RcsGui PROPERTIES AUTOMOC TRUE)

TARGET_INCLUDE_DIRECTORIES(RcsGui PUBLIC
    # Header source location
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    
    # Header install location
    $<INSTALL_INTERFACE:include/RcsGui>
    
    # Regular dependencies
    ${QT_QTGUI_INCLUDE_DIR}
    ${QT_QTCORE_INCLUDE_DIR}
    ${QT_INCLUDE_DIR})
TARGET_INCLUDE_DIRECTORIES(RcsGui PRIVATE ${QWT_INCLUDE_DIRS})

# copy the .dll file to the same folder as the executable
IF (WIN32)
ADD_CUSTOM_COMMAND(
    TARGET RcsGui POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${LIBRARY_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}/RcsGui.dll
    ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}/RcsGui.dll)
ENDIF()

# Mark for export
RCS_ADD_EXPORT_LIBRARY(RcsGui)

# Installation
# Headers
INSTALL(
  DIRECTORY . 
  DESTINATION include/RcsGui
  FILES_MATCHING PATTERN "*.h*"
)
# Install the binaries
INSTALL(TARGETS RcsGui EXPORT RcsExport DESTINATION lib)
