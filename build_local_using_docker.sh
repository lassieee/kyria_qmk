#!/bin/bash

docker run --platform linux/amd64 -d --rm --name qmk qmkfm/qmk_cli sleep 300;
docker exec -it qmk python3 -m pip install qmk
docker exec -it qmk qmk setup -y
docker exec -it qmk qmk env
docker cp lassieee qmk:qmk_firmware/keyboards/splitkb/kyria/keymaps
docker exec -it qmk qmk compile -kb splitkb/kyria/rev2 -km lassieee
docker cp qmk:/qmk_firmware/splitkb_kyria_rev2_lassieee.hex .
docker stop qmk
