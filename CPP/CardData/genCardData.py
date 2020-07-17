import xlrd
import json
import os
import sys
import getopt
import pprint

# DEFINE GLOBALS
global verboseLevel
global dataDictionary
global pp

verboseLevel = ""
dataDictionary = {}
pp = pprint.PrettyPrinter(indent=4)

# Define json fields
jsonFileDesc     = "Master Card List"
jsonRelease      = "-"
jsonVersion      = "1.0"

# Card defines
jsonName         = ""
jsonID           = ""
jsonRarity       = ""
jsonDeckLimit    = ""
jsonFirstAction  = ""
jsonSecondAction = ""
jsonCardDesc     = ""
jsonCardReleased = ""

# Spreadsheet to json field mapping
idColNum        = 0
releasedColNum  = 1
deckLimitColNum = 2
rarityColNum    = 3
typeColNum      = 4
classColNum     = 5
subclassColNum  = 6
nameColNum      = 7
actOneColNum    = 8
actTwoColNum    = 9
descColNum      = 10

# FUNCTION:
#   createJson()
#
# PARAMETERS:
#   fileName    - name of file to save to
#
# DESCRIPTION:
#   Creates json file from data parsed in parseXlsx()
def createJson(fileName):
  print("create stay gold")
  global dataDictionary
  global pp

  #temp = json.loads(dataDictionary)
  with open(fileName, "w") as outfile:
    json.dump(dataDictionary, outfile, indent=2)

# FUNCTION:
#   parseXlsx()
#
# PARAMETERS:
#   fileName    - name of file to parse
#
# DESCRIPTION:
#   Parses .xlsx file. See help() to see columns parsed
#   Creates data dictionary for createJson()
def parseXlsx(fileLoc):
  print("parse stay gold")

  global verboseLevel
  global dataDictionary
  global pp

  # Open spreadsheet
  workbook = xlrd.open_workbook(fileLoc)
  dataSheet = workbook.sheet_by_index(0)

  dataDictionary.update({"Data Description" : jsonFileDesc})
  dataDictionary.update({"Release" : jsonRelease})
  dataDictionary.update({"Version" : jsonVersion})

  cardArrayIdx = 0
  cardArray = []
  cardDictionary = {}

  # Skip header row
  rowIdx = 1
  while rowIdx < dataSheet.nrows:
    # Clear dictionary to read new row in spreadsheet
    cardDictionary = {}

    # Read cell values
    cardId    = int(dataSheet.cell_value(rowIdx, idColNum))
    released  = dataSheet.cell_value(rowIdx, releasedColNum)
    decklimit = int(dataSheet.cell_value(rowIdx, deckLimitColNum))
    rarity    = dataSheet.cell_value(rowIdx, rarityColNum)
    cardType  = dataSheet.cell_value(rowIdx, typeColNum)
    cardClass = dataSheet.cell_value(rowIdx, classColNum)
    subclass  = dataSheet.cell_value(rowIdx, subclassColNum)
    name      = dataSheet.cell_value(rowIdx, nameColNum)
    actionOne = dataSheet.cell_value(rowIdx, actOneColNum)
    actionTwo = dataSheet.cell_value(rowIdx, actTwoColNum)
    cardDesc  = dataSheet.cell_value(rowIdx, descColNum)

    # Add cell values to dictionary
    cardDictionary.update({"Name"          : name})
    cardDictionary.update({"ID"            : cardId})
    cardDictionary.update({"Released"      : released})
    cardDictionary.update({"Rarity"        : rarity})
    cardDictionary.update({"Type"          : cardType})
    cardDictionary.update({"Class"         : cardClass})
    cardDictionary.update({"Subclass"      : subclass})
    cardDictionary.update({"Deck Limit"    : decklimit})
    cardDictionary.update({"First Action"  : actionOne})
    cardDictionary.update({"Second Action" : actionTwo})
    cardDictionary.update({"Description"   : cardDesc})

    # Add card data (row from spreadsheet) to array
    cardArray.append(cardDictionary)

    rowIdx += 1
    cardArrayIdx += 1
    # End of while loop

  if verboseLevel == "high":
    print("Leaving parseXlsx while loop")

  # Add list of cards to dictionary
  dataDictionary.update({"Card" : cardArray})

  if verboseLevel == "high":
    pp.pprint(dataDictionary)


# FUNCTION:
#    help()
#
# DESCRIPTION:
#   When -h or --help argument is passed this function is
#   ran and displays all command line arguments
def help():
  help_string = """
  This script will parse an .xlsx file and generate a .json file\n
  Things to check
    1. Default file to parse is in this directory with the name cardList.xlsx
    2. Desired sheet to parse is first in the workbook
    3. Data in the sheet is organized as below
      Column 0 : ID
      Column 1 : STATUS
      Column 2 : DECK LIMIT
      Column 3 : RARITY
      Column 4 : TYPE      -- Currently not used
      Column 5 : CLASS     -- Currently not used
      Column 6 : SUBCLASS  -- Currently not used
      Column 7 : NAME
      Column 8 : Action 1
      Column 9 : Action 2
      Column 10: Description

      -h, --help      prints this to screen
      -f, --file    <filename>    path to non-default file to parse
      -j, --json    <filename>    name of non-default json file to save to
      -v, --verbose <HIGH | LOW>  prints extra information
  """
  print(help_string)

# Define main function
def main(argv):
  print("stay gold")
  global verboseLevel

  # Get Default File Location
  cwd = os.getcwd()
  xlsxFileLoc = (cwd + "\cardList.xlsx")
  jsonFileName = "cardData.json"

  try:
    opts, args = getopt.getopt(argv, "hf:v:j",
    ["file=", "json=", "verbose="])
  except getopt.GetoptError:
    help()
    sys.exit(2)

  for opt, arg in opts:
    if opt == "-h" or opt == "--help":
      help()
      sys.exit()
    elif opt == "-f" or opt == "--file":
      xlsxFileLoc = arg
    elif opt == "-j" or opt == "--json":
      jsonFileName = arg
    elif opt == "--verbose":
      if arg.lower() == "high" or arg.lower() == "low":
        verboseLevel = arg.lower()
    elif opt == "-v":
      verboseLevel = "high"

  parseXlsx(xlsxFileLoc)
  createJson(jsonFileName)

if __name__ == "__main__":
  main(sys.argv[1:])