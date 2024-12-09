# Shapes

To run this application, make sure to have bash, cmake and make installed.

How to setup build:

mkdir build #if not yet created

cd build

rm -rf * #If running on a new system, make sure to delete previous build.

cmake .. #builds inside the new build directory

make

Run the application:

cd build

./src/ShapesApp

Run the unit tests:

cd build

./tst/runTests
