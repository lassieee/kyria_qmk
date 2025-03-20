#!/bin/bash

rev=$1
qmkhome=/home/casper/dev/git/github/qmk_firmware

if [[ -z ${rev} ]]; then
  echo ''
  echo 'please specify for which revision you wish to build firmware for'
  echo "supported revisions are '1' or '2', e.g. ${0} 2"
  exit 1
fi

# determine container engine
if [[ $(which docker) ]]; then
  export ce=docker
elif [[ $(which podman) ]]; then
  export ce=podman
else
  echo 'neither docker nor podman container engine found..'
  exit 1
fi

${ce} run --platform linux/amd64 -d --rm \
  -v "${qmkhome}:/qmk_firmware:z" \
  --name qmk \
  ghcr.io/qmk/qmk_cli sleep 500

${ce} exec -it qmk qmk setup -y
${ce} exec -it qmk qmk env
${ce} cp lassieee qmk:qmk_firmware/keyboards/splitkb/kyria/keymaps
${ce} exec -it qmk qmk compile -kb splitkb/kyria/rev${rev} -km lassieee
${ce} cp qmk:/qmk_firmware/splitkb_kyria_rev${rev}_base_lassieee.hex .
${ce} stop qmk
