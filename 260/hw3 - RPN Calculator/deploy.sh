#!/bin/bash
DEST_IP="$1"
DEST_PORT="$2"
DEST_USER="$3"
DEBUG_PORT="$4"
BINARY="$5"
DEST_DIR="~"

# kill gdbserver on tx8m and delete old binary
ssh -p ${DEST_PORT} ${DEST_USER}@${DEST_IP} "sh -c '/usr/bin/pkill gdbserver; rm -rf ${DEST_DIR}/${BINARY}  exit 0'"

# send binary to target
scp -P ${DEST_PORT} ${BINARY} ${DEST_USER}@${DEST_IP}:${DEST_DIR}/${BINARY}

# start gdbserver on target
ssh -t -p ${DEST_PORT} ${DEST_USER}@${DEST_IP} "sh -c 'cd ${DEST_DIR}; gdbserver localhost:${DEBUG_PORT} ${BINARY}'"
