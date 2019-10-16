#!/bin/bash
if [ $# -gt 1 ]
then
  send_user "Error, no argument , usage: expect  crtMvnProj.exp projName\n"
  exit
else
  mvn archetype:generate -DgroupId=glx.cn.sh -DartifactId=$1 -Dversion=1.0-SNAPSHOT -DarchetypeArtifactId=maven-archetype-quickstart -DinteractiveMode=false -DarchetypeVersion=RELEASE
fi
