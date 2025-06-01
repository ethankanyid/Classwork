#!/bin/bash

echo $$
exec > debug.log 2>&1
exec < /dev/null
exec ./main
