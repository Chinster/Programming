// Performs face detection outlining each face.
// Can crop face to a file.
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv/cv.hpp>

#include <string.h>

#define CASCADE_PREFIX "/usr/share/opencv/haarcascades/"
#define FACE_CASCADE "/usr/share/opencv/haarcascades/haarcascade_frontalface_default.xml"
#define EYE_CASCADE "/usr/share/opencv/haarcascades/haarcascade_eye.xml"
void face_detect(cv::Mat image, std::string outfile) {
    // Convert image to gray
    cv::Mat gray_image;
    cv::cvtColor(image, gray_image, CV_BGR2GRAY);

    // Prepare face detectors
    cv::CascadeClassifier face_cascade(FACE_CASCADE);
    cv::CascadeClassifier eye_cascade(EYE_CASCADE);

    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(gray_image, faces, 1.1, 2);

    for (int i = 0; i < faces.size(); i++) {
        cv::Rect face_region = faces[i];
        int x = face_region.x;
        int y = face_region.y;
        int w = face_region.width;
        int h = face_region.height;

        // Crop image with roi and save.
        if (outfile != "") {
            cv::Mat crop(image, face_region);
            std::string out_name = std::to_string(i) + outfile;
            cv::imwrite(out_name, crop);
        }

        cv::rectangle(image, cv::Point(x, y), cv::Point(x + w, y + h), cv::Scalar(0, 0, 255), 2);

        // Generate a region of interest of face
        cv::Mat roi_gray(gray_image, face_region);

        // Detect eyes in face
        std::vector<cv::Rect> eyes;
        eye_cascade.detectMultiScale(roi_gray, eyes, 1.1, 2);
        for (int j = 0; j < eyes.size(); j++) {
            cv::Rect eye_region = eyes[j];
            int ex = eye_region.x;
            int ey = eye_region.y;
            int ew = eye_region.width;
            int eh = eye_region.height;

            cv::Point point1(x + ex, y + ey);
            cv::Point point2(x + ex + ew, y + ey + eh);

            cv::rectangle(image, point1, point2, cv::Scalar(255, 0, 0), 2);
        }

    }
}

int main(int argc, char *argv[])
{

    // Read image
    cv::Mat image = cv::imread(argv[1], 1);
    if (!image.data) {
        printf("Error loading image %s\n", argv[1]);
        return 2;
    }

    if (argc == 3)
        face_detect(image, argv[2]);
    else
        face_detect(image, "");
    cv::namedWindow("image", CV_WINDOW_AUTOSIZE);
    cv::imshow("image", image);
    cv::waitKey(0);
    return 0;
}
