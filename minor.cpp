// #include <stdio.h>
// #include <stdlib.h>
// #include <opencv2/opencv.hpp>
// #include <opencv2/xfeatures2d.hpp>

// #pragma pack(push, 1)
// typedef struct {
//     unsigned short bfType;
//     unsigned int bfSize;
//     unsigned short bfReserved1;
//     unsigned short bfReserved2;
//     unsigned int bfOffBits;
// } BMPHeader;

// typedef struct {
//     unsigned int biSize;
//     int biWidth;
//     int biHeight;
//     unsigned short biPlanes;
//     unsigned short biBitCount;
//     unsigned int biCompression;
//     unsigned int biSizeImage;
//     int biXPelsPerMeter;
//     int biYPelsPerMeter;
//     unsigned int biClrUsed;
//     unsigned int biClrImportant;
// } DIBHeader;
// #pragma pack(pop)

// // Function to convert an image to grayscale
// void convertToGrayscale(const char *inputFile, const char *outputFile) {
//     // Load the image
//     cv::Mat img = cv::imread(inputFile, cv::IMREAD_COLOR);
//     if (img.empty()) {
//         fprintf(stderr, "Could not open or find the image: %s\n", inputFile);
//         return;
//     }

//     // Convert to grayscale
//     cv::Mat grayImg;
//     cv::cvtColor(img, grayImg, cv::COLOR_BGR2GRAY);

//     // Save the grayscale image
//     cv::imwrite(outputFile, grayImg);
// }

// // Function to extract SURF features and classify as forged or not
// void classifyImage(const char *originalFile, const char *suspectFile) {
//     // Load the original and suspect images
//     cv::Mat originalImg = cv::imread(originalFile, cv::IMREAD_GRAYSCALE);
//     cv::Mat suspectImg = cv::imread(suspectFile, cv::IMREAD_GRAYSCALE);
    
//     if (originalImg.empty() || suspectImg.empty()) {
//         fprintf(stderr, "Could not open or find the images.\n");
//         return;
//     }

//     // Initialize SURF detector
//     int minHessian = 400;
//     cv::Ptr<cv::xfeatures2d::SURF> detector = cv::xfeatures2d::SURF::create(minHessian);

//     // Detect keypoints and compute descriptors
//     std::vector<cv::KeyPoint> keypoints1, keypoints2;
//     cv::Mat descriptors1, descriptors2;
//     detector->detectAndCompute(originalImg, cv::noArray(), keypoints1, descriptors1);
//     detector->detectAndCompute(suspectImg, cv::noArray(), keypoints2, descriptors2);

//     // Match descriptors using BFMatcher
//     cv::BFMatcher matcher(cv::NORM_L2);
//     std::vector<cv::DMatch> matches;
//     matcher.match(descriptors1, descriptors2, matches);

//     // Filter matches based on distance
//     double max_dist = 0; 
//     double min_dist = 100;
//     for (int i = 0; i < matches.size(); i++) {
//         double dist = matches[i].distance;
//         if (dist < min_dist) min_dist = dist;
//         if (dist > max_dist) max_dist = dist;
//     }

//     // Keep only good matches (e.g., those that are less than 3 times the min distance)
//     std::vector<cv::DMatch> good_matches;
//     for (int i = 0; i < matches.size(); i++) {
//         if (matches[i].distance <= std::max(3 * min_dist, 0.02)) {
//             good_matches.push_back(matches[i]);
//         }
//     }

//     // Classify based on the number of good matches
//     if (good_matches.size() > 100) { // Threshold can be adjusted
//         printf("The image is likely NOT forged. Good matches: %lu\n", good_matches.size());
//     } else {
//         printf("The image is likely FORGED. Good matches: %lu\n", good_matches.size());
//     }

//     // Draw matches for visualization
//     cv::Mat imgMatches;
//     cv::drawMatches(originalImg, keypoints1, suspectImg, keypoints2, good_matches, imgMatches);
    
//     // Show the matches
//     cv::imshow("Good Matches", imgMatches);
//     cv::waitKey(0);
    
//     // Show the classification result
//     if (good_matches.size() > 100) {
//         cv::putText(imgMatches, "Result: NOT FORGED", cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);
//     } else {
//         cv::putText(imgMatches, "Result: FORGED", cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
//     }
    
//     // Display the result on the image with matches
//     cv::imshow("Good Matches with Result", imgMatches);
//     cv::waitKey(0);
// }

// int main() {
//     const char *inputFile = "/Users/atishay/minor/1.bmp"; // Original image
//     const char *outputFile = "/Users/atishay/minor/output3.bmp"; // Grayscale image
//     const char *suspectFile = "/Users/atishay/minor/suspect.bmp"; // Suspect image

//     convertToGrayscale(inputFile, outputFile);
//     classifyImage(outputFile, suspectFile);

//     return 0;
// }
