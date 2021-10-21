
#############################################################
# pippi: parse it, plot it
# ------------------------
# Colour scheme module for pippi.  Add your own at the end of
# this file.
#
# Author: Pat Scott (patscott@physics.mcgill.ca)
# Originally developed: March 2012
#############################################################

import re
import copy

permittedSchemes = {}

def Blockshading(colour,line_code, fill_code):
  scheme = colourScheme('Blockshading_'+colour)
  scheme.baseProfColourMap = '#fff--#fff(contour1)--#'+fill_code+'(contour1)--#'+fill_code
  scheme.basePostColourMap = '#fff--#fff(contour1)--#'+fill_code+'(contour1)--#'+fill_code
  scheme.mainPostContourColour2D = '\'#'+line_code+'\''
  scheme.mainProfContourColour2D = '\'#'+line_code+'\''
  scheme.mainBestFitColour1D = '#'+line_code
  scheme.mainPostMeanColour1D = '#'+line_code
  scheme.mainBestFitColour2D = '#'+line_code
  scheme.mainPostMeanColour2D = '#'+line_code
  scheme.fillTransparency2D = '0.85' #so far this is not actually functional in ctioga2; presumably it will work in later versions.
  return scheme


class colourScheme:
  # Class for pippi plotting colour schemes

  # Name of colour scheme
  name = ''

  # Default values for colours
  mainPostColour1D = 'Blue'
  mainProfColour1D = 'Red'
  mainPostContourColour2D = 'Black'
  mainProfContourColour2D = 'Black'
  comparisonPostColour1D = 'Grey'
  comparisonProfColour1D = 'Grey'
  comparisonPostContourColour2D = 'Grey'
  comparisonProfContourColour2D = 'Grey'
  baseProfColourMap = '#fff--#fff(contour2)--#f45(contour1)--#612'
  basePostColourMap = '#fff--#fff(contour2)--#88f(contour1)--#229'

  # Default values for 1D plotting styles
  fillTransparency1D = '0.85'
  main1DLineStyle = 'Solid'
  comparison1DLineStyle = 'Solid' #alt: 'Dots', 'Dashes'
  lineWidth1D = '0.9'

  # Default values for 2D contour plotting styles
  fillTransparency2D = '1.0'
  mainContourStyle = 'Solid'
  comparisonContourStyle = 'Solid'
  lineWidth2D = '0.9'

  # Default text and axis colours
  legendTextColour1D = 'Black'
  keyTextColour1D = 'Black'
  axisColour1D = 'Black'
  legendTextColour2D = 'Black'
  keyTextColour2D = 'Black'
  axisColour2D = 'Black'

  # Default markers and their colours
  referenceMarkerInner = 'Cross'
  referenceMarkerInnerScale = 0.7
  referenceMarkerInnerColour = 'Black'
  referenceMarkerOuter = 'Times'
  referenceMarkerOuterScale = 0.7
  referenceMarkerOuterColour = 'Yellow'

  mainBestFitMarker = 'Star'
  mainBestFitMarkerScale = 0.8
  mainBestFitColour1D = '#300'
  mainBestFitColour2D = '#300'
  mainBestFitColourOutline2D = 'Black'

  mainPostMeanMarker = 'Bullet'
  mainPostMeanMarkerScale = 0.6
  mainPostMeanColour1D = '#004'
  mainPostMeanColour2D = '#004'
  mainPostMeanColourOutline2D = 'Black'

  comparisonBestFitMarker = 'Star'
  comparisonBestFitMarkerScale = 0.8
  comparisonBestFitColour = 'Grey'

  comparisonPostMeanMarker = 'Bullet'
  comparisonPostMeanMarkerScale = 0.6
  comparisonPostMeanColour = 'Grey'

  def __init__(self,name):
    global permittedSchemes
    name = name.lower()
    self.name = name
    if permittedSchemes is None:
      permittedSchemes = {name:self}
    else:
      permittedSchemes[name] = self

  def colourMap(self,contours,kind):
    #Construct colourmap from base colour map and contour levels
    if kind == 'post':
      localColourMap = self.basePostColourMap
    elif kind == 'like':
      localColourMap = self.baseProfColourMap
    elif kind == 'obs':
      localColourMap = self.baseObsColourMap
    else:
      sys.exit('    Error: unrecognised type of colourmap requested.\n    Quitting...\n')
    for i, contour in enumerate(contours):
      localColourMap = re.sub(r'contour'+str(i+1), contour, localColourMap)
    return localColourMap

# basic colour scheme
basic = colourScheme('basic')

# iceCube colour scheme
iceCube = colourScheme('iceCube')
iceCube.baseProfColourMap = '#fff--#fff(contour2)--#292(contour1)--#f55(contour1)--#000'
iceCube.basePostColourMap = '#fff--#fff(contour2)--#29d(contour1)--#f55(contour1)--#000'
iceCube.baseObsColourMap = 'hls:White(contour1)--Red(contour2)--Green(contour3)'
iceCube.mainBestFitColour1D = 'Black'
iceCube.mainPostMeanColour1D = 'Black'
iceCube.mainBestFitColour2D = 'Black'
iceCube.mainPostMeanColour2D = 'Black'

# iceCube79 colour scheme
iceCube79 = colourScheme('iceCube79')
iceCube79.baseProfColourMap = '#fff--#fff(contour2)--#fab(contour1)--#f45'
iceCube79.basePostColourMap = '#fff--#fff(contour2)--#ddf(contour1)--#88f'
iceCube79.baseObsColourMap = 'hls:White(contour1)--Red(contour2)--Green(contour3)'
iceCube79.mainBestFitColour1D = 'Black'
iceCube79.mainPostMeanColour1D = 'Black'
iceCube79.mainBestFitColour2D = 'Black'
iceCube79.mainPostMeanColour2D = 'Black'
iceCube79.mainPostContourColour2D = 'Grey'
iceCube79.mainProfContourColour2D = 'Grey'
iceCube79.lineWidth2D = '1.5'

# iceCube3sig colour scheme
iceCube3sig = colourScheme('iceCube3sig')
iceCube3sig.baseProfColourMap = '#fff--#fff(contour3)--#292(contour2)--#fff(contour2)--#929(contour1)--#f55(contour1)--#000'
iceCube3sig.basePostColourMap = '#fff--#fff(contour3)--#29d(contour2)--#fff(contour2)--#929(contour1)--#f55(contour1)--#000'
iceCube3sig.baseObsColourMap = 'hls:White(contour1)--Red(contour2)--Green(contour3)'
iceCube3sig.mainBestFitColour1D = 'Black'
iceCube3sig.mainPostMeanColour1D = 'Black'
iceCube3sig.mainBestFitColour2D = 'Black'
iceCube3sig.mainPostMeanColour2D = 'Black'

# SBClassic colour scheme
SBClassic = colourScheme('SBClassic')
SBClassic.baseProfColourMap = '#fff--#fff(contour2)--#2f2(contour1)--#f33(0.5)--#000'
SBClassic.basePostColourMap = '#fff--#fff(contour2)--#95d(contour1)--#f33(0.5)--#000'
SBClassic.baseObsColourMap = 'hls:White(contour1)--Red(contour2)--Green(contour3)'
SBClassic.mainBestFitColour1D = 'Black'
SBClassic.mainPostMeanColour1D = 'Black'
SBClassic.mainBestFitColour2D = 'Black'
SBClassic.mainPostMeanColour2D = 'Black'

# BlueGold colour scheme
BlueGold = colourScheme('BlueGold')
BlueGold.baseProfColourMap = '#fff--#fff(contour2)--#f44(contour2)--#f44(contour1)--#ece(contour1)--#ece'
BlueGold.basePostColourMap = '#fff--#fff(contour2)--#44f(contour2)--#44f(contour1)--#fc0(contour1)--#fc0'
BlueGold.baseObsColourMap = 'hls:White(contour1)--Red(contour2)--Green(contour3)'
BlueGold.mainPostContourColour2D = 'DarkBlue'
BlueGold.mainProfContourColour2D = 'Maroon'
BlueGold.mainBestFitColour = 'Black'
BlueGold.mainBestFitColour1D = 'Black'
BlueGold.mainPostMeanColour1D = 'Black'
BlueGold.mainBestFitColour2D = 'Black'
BlueGold.mainPostMeanColour2D = 'Black'

# nightOfTheAllanachs colour scheme
nightOfTheAllanachs = colourScheme('nightOfTheAllanachs')
nightOfTheAllanachs.basePostColourMap = '#000--#000(contour2)--#808(contour1)--#f33(0.5)--#ff0'
nightOfTheAllanachs.baseProfColourMap = '#000--#000(contour2)--#33f(contour1)--#0ff(0.5)--#ff0'
nightOfTheAllanachs.baseObsColourMap = 'Black(contour1)--Red(contour2)--Green(contour3)'
nightOfTheAllanachs.mainPostContourColour2D = 'White'
nightOfTheAllanachs.mainProfContourColour2D = 'White'
nightOfTheAllanachs.axisColour2D = 'White'
nightOfTheAllanachs.mainBestFitColour1D = 'Black'
nightOfTheAllanachs.mainPostMeanColour1D = 'Black'
nightOfTheAllanachs.mainBestFitColour2D = 'White'
nightOfTheAllanachs.mainPostMeanColour2D = 'White'
nightOfTheAllanachs.legendTextColour2D = 'White'
nightOfTheAllanachs.keyTextColour2D = 'White'
nightOfTheAllanachs.comparisonContourStyle = 'Dashes'
nightOfTheAllanachs.comparison1DLineStyle = 'Dashes'

# nightOfTheAllanachs2 colour scheme
nightOfTheAllanachs2 = colourScheme('nightOfTheAllanachs2')
nightOfTheAllanachs2.basePostColourMap = '#000--#000(contour2)--#808(contour1)--#f33(0.5)--#ff0'
nightOfTheAllanachs2.baseProfColourMap = '#000--#000(contour2)--#33f(contour1)--#0ff(0.5)--#ff0'
nightOfTheAllanachs2.baseObsColourMap = 'Black(contour1)--Red(contour2)--#00FFFF(contour3)'
nightOfTheAllanachs2.mainPostContourColour2D = 'White'
nightOfTheAllanachs2.mainProfContourColour2D = 'White'
nightOfTheAllanachs2.axisColour2D = 'White'
nightOfTheAllanachs2.mainBestFitColour1D = 'Red'
nightOfTheAllanachs2.mainPostMeanColour1D = 'Blue'
nightOfTheAllanachs2.mainBestFitColour2D = 'White'
nightOfTheAllanachs2.mainBestFitColourOutline2D = 'Black'
nightOfTheAllanachs2.mainPostMeanColour2D = 'White'
nightOfTheAllanachs2.mainPostMeanColourOutline2D = 'Black'
nightOfTheAllanachs2.legendTextColour2D = 'White'
nightOfTheAllanachs2.keyTextColour2D = 'White'
nightOfTheAllanachs2.comparisonContourStyle = 'Dashes'
nightOfTheAllanachs2.comparison1DLineStyle = 'Dashes'

# nightOfTheAllanachs3 colour scheme
nightOfTheAllanachs3 = colourScheme('nightOfTheAllanachs3')
nightOfTheAllanachs3.basePostColourMap = '#000--#000(contour2)--#808(contour1)--#f33(0.5)--#ff0'
nightOfTheAllanachs3.baseProfColourMap = '#000--#000(contour2)--#33f(contour1)--#0ff(0.5)--#ff0'
nightOfTheAllanachs3.baseObsColourMap = 'Black(contour1)--Blue(contour2)--Orange(contour3)'
nightOfTheAllanachs3.mainPostContourColour2D = 'White'
nightOfTheAllanachs3.mainProfContourColour2D = 'White'
nightOfTheAllanachs3.axisColour2D = 'White'
nightOfTheAllanachs3.mainBestFitColour1D = 'Red'
nightOfTheAllanachs3.mainPostMeanColour1D = 'Blue'
nightOfTheAllanachs3.mainBestFitColour2D = 'White'
nightOfTheAllanachs3.mainBestFitColourOutline2D = 'Black'
nightOfTheAllanachs3.mainPostMeanColour2D = 'White'
nightOfTheAllanachs3.mainPostMeanColourOutline2D = 'Black'
nightOfTheAllanachs3.legendTextColour2D = 'White'
nightOfTheAllanachs3.keyTextColour2D = 'White'
nightOfTheAllanachs3.comparisonContourStyle = 'Dashes'
nightOfTheAllanachs3.comparison1DLineStyle = 'Dashes'

# Blockshading colour schemes
Blockshading_red = Blockshading("red", "800", "e00")
Blockshading_green = Blockshading("green", "080", "0e0")
Blockshading_blue = Blockshading("blue", "005", "44f")
Blockshading_pink = Blockshading("pink", "808", "e0e")
Blockshading_purple = Blockshading("purple", "303", "80e")
Blockshading_orange = Blockshading("orange", "840", "f90")
Blockshading_yellow = Blockshading("yellow", "870", "fe0")
Blockshading_cyan = Blockshading("cyan", "088", "3ee")
