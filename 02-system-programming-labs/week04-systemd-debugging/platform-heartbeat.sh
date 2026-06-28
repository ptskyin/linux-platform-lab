#!/usr/bin/env bash
set -euo pipefail

LOG_FILE="/tmp/platform-heartbeat.log"
COUNTER=1

while true; do
  echo "$(date -Iseconds) heartbeat #$COUNTER" >> "$LOG_FILE"
  COUNTER=$((COUNTER + 1))
  sleep 5
  exit 0
done
