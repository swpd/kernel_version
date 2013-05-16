kernel version : a Duda web service
====================================

This is a web service that return the kernel version of server based on Duda
web service framework.

## Introduction ##
This web service(kernel\_version) reads information from file /proc/version and
prints the required version information.

## Installation ##
clone this repository:

    git clone https://github.com/swpd/kernel_version.git

## Running web service ##
use DudaC to set up this web service, it makes running web service an easy task.
if you haven't set up DudaC, check out [this](http://duda.io/documentation/dudac).

change to DudaC's directory:

    cd dudac/

run the web service:

    ./dudac -w /path/to/kernel_version/

for example, if you have kernel\_version repo downloaded in your home directory,
run the following command:

    ./dudac -w ~/kernel_version/

yes, that's it. if no errors occur our web service shall be up and running.

## Serving requests ##
use your favorite client to visit the following URL to retrieve the version
information of server:

    http://localhost:2001/kernel_version/
