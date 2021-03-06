#!/bin/bash
# Let the student work on the concept map

# Load scripts
. ../../testing_cpp_gui_applications_tutorial/scripts/get_dialog_id.sh

# Variables
myexe="../../build-BrainweaverDeveloper-Desktop-Debug/BrainweaverDeveloper"

####################################
# Check executable
####################################
if [ -e /$myexe ] # slash is obligatory?
then
  echo $mytestname": FAIL (executable '"$myexe"' not found)"
  exit
fi

####################################
# Start application
####################################
$myexe &
sleep 1

####################################
# Main menu, choose '4. Cluster dialog'
####################################
id=`get_dialog_id "Menu voor de ontwikkelaar"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi
xdotool windowactivate $id key alt+4 sleep 0.2

