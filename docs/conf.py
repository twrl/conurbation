#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os, subprocess, sys

extensions = [ 'sphinx.ext.autodoc', 'sphinx.ext.todo', 'sphinx.ext.viewcode', 'breathe' ]

breathe_projects = { "Conurbation": "dox/xml" }
breathe_default_project = "Conurbation"

master_doc = "index"

def run_doxygen():
    try:
        subprocess.call("doxygen", shell = True)
    except OSError as e:
        sys.stderr.write("doxygen execution failed: %s" % e)

def generate_doxygen(app):

    rtd_build = os.environ.get("READTHEDOCS", None) == "True"

    if rtd_build:
        run_doxygen()

def setup(app):
    app.connect("builder-inited", generate_doxygen)
