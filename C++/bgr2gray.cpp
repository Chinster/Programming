// Converts an image in BGR to Grayscale.
// Receives image as program argument.
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv/cv.hpp>
#include <string.h>

int main(int argc, char *argv[])
{
    std::string imageName = argv[1];

    cv::Mat image = cv::imread(imageName, 1);

    if (argc != 2 || !image.data) {
        printf("No image data\n");
        return -1;
    }

    cv::Mat gray_image;
    cv::cvtColor(image, gray_image, CV_BGR2GRAY);

    std::string gray_image_name = "gray_" + imageName;
    cv::imwrite(gray_image_name, gray_image);

    cv::namedWindow(imageName, CV_WINDOW_AUTOSIZE);
    cv::namedWindow("Gray image", CV_WINDOW_AUTOSIZE);

    cv::imshow(imageName, image);
    cv::imshow("Gray image", gray_image);

    cv::waitKey(0);

    return 0;
}
