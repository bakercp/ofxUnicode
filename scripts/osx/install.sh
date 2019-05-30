#!/usr/bin/env bash
set -e

# This is needed for raqm.
if ! [ -x "$(command -v gtkdocize)" ]; then
    brew install gtk-doc
fi
