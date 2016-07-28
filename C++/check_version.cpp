// Checks openCV version and capabilities
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;

int main(int argc, char** argv)
{
    std::cout <<
        "Using OpenCV version " << CV_VERSION << "\n" << std::endl;

    std::cout << getBuildInformation();

    return 0;
}
