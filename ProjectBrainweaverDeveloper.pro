#DEFINES += BRAINWEAVER_MOVE_ITEMS_ON_COLLISION

#Don't enable Effective C++ warnings when using Qwt
include(../RibiLibraries/DesktopApplication.pri)
include(../RibiLibraries/Apfloat.pri)
include(../RibiLibraries/Boost.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

include(../RibiLibraries/GeneralConsole.pri)
include(../RibiLibraries/GeneralDesktop.pri)

#Specific, console
include(../RibiClasses/CppContainer/CppContainer.pri)
include(../RibiClasses/CppCounter/CppCounter.pri)
include(../RibiClasses/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../RibiClasses/CppGeometry/CppGeometry.pri)
include(../RibiClasses/CppGrabber/CppGrabber.pri)
include(../RibiClasses/CppPlane/CppPlane.pri)
include(../RibiClasses/CppQtImage/CppQtImage.pri)
include(../RibiClasses/CppRibiRandom/CppRibiRandom.pri)
include(../RibiClasses/CppRibiRegex/CppRibiRegex.pri)
include(../RibiClasses/CppStopwatch/CppStopwatch.pri)

include(../RibiClasses/CppQtArrowItem/CppQtArrowItem.pri)
include(../RibiClasses/CppQtDisplayPosItem/CppQtDisplayPosItem.pri)
include(../RibiClasses/CppQtGraphics/CppQtGraphics.pri)
include(../RibiClasses/CppQtKeyboardFriendlyGraphicsView/CppQtKeyboardFriendlyGraphicsView.pri)
include(../RibiClasses/CppQtLabeledQuadBezierArrowItem/CppQtLabeledQuadBezierArrowItem.pri)
include(../RibiClasses/CppQtPathArrowItem/CppQtPathArrowItem.pri)
include(../RibiClasses/CppQtQuadBezierArrowItem/CppQtQuadBezierArrowItem.pri)
include(../RibiClasses/CppQtRoundedEditRectItem/CppQtRoundedEditRectItem.pri)
include(../RibiClasses/CppQtRoundedRectItem/CppQtRoundedRectItem.pri)
include(../RibiClasses/CppQtScopedDisable/CppQtScopedDisable.pri)
include(../RibiClasses/CppTrace/CppTrace.pri)
include(../RibiClasses/CppXml/CppXml.pri)

#Specific
include(../RibiClasses/CppConceptMap/CppConceptMap.pri)
include(../StyleSheetSetter/ToolStyleSheetSetterDesktop.pri)
include(../TestConceptMap/ToolTestConceptMapDesktop.pri)
include(../TestArrowItems/ToolTestQtArrowItemsDesktop.pri)
include(../TestRoundedEditRectItem/ToolTestQtRoundedEditRectItemDesktop.pri)
include(../TestRoundedRectItem/ToolTestQtRoundedRectItemDesktop.pri)

#Desktop
include(../RibiClasses/CppQtConceptMap/CppQtConceptMap.pri)
include(ProjectBrainweaverDesktop.pri)

SOURCES += qtmain_developer.cpp
