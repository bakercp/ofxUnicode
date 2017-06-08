#!/bin/bash
set -e

# Download dlib models and media.

echo "Downloading models and data ..."

ADDON_PATH=$( cd $(dirname $0)/../../ ; pwd -P )
SCRIPTS_PATH=$ADDON_PATH/scripts
MODELS_PATH=$ADDON_PATH/models
DATA_PATH=$ADDON_PATH/data


echo ""
echo "Installing example models ..."

for required_models in `ls $ADDON_PATH/example*/bin/data/required_models.txt`
do
  while read model || [ -n "$model" ];
  do
    echo $required_models
    rsync -Prvaq $MODELS_PATH/$model $(dirname $required_models)
  done < $required_models
  echo ""
done

echo ""
echo "Installing example data ..."

for required_data in `ls $ADDON_PATH/example*/bin/data/required_data.txt`
do
  while read data || [ -n "$data" ];
  do
    echo $required_data
    rsync -Prvaq $DATA_PATH/$data $(dirname $required_data)
  done < $required_data
  echo ""
done

echo ""
echo "Downloading example media ..."

for required_media in `ls $ADDON_PATH/example*/bin/data/required_media.txt`
do
  # Move into this directory. > /dev/null consumes the output.
  pushd $(dirname $required_media)/ > /dev/null

  # The || [ -n "$line" ]; is to help when the last line isn't a new line char.
  while read line || [ -n "$line" ];
  do
    tokens=($line)
    destination=${tokens[0]}
    url=${tokens[1]}

    if ! [ -f $destination ] ; then
      echo "Downloading $url"
      curl -L -o $destination --progress-bar $url
    else
      echo "- Exists: Skipping $destination"
    fi
  done < $required_media
  popd > /dev/null
  echo ""
done

