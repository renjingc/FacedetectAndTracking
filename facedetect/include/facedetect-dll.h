#ifndef FACEDETECT_DLL_H
#define FACEDETECT_DLL_H

#ifdef FACEDETECTDLL_EXPORTS
#define FACEDETECTDLL_API __declspec(dllexport) 
#else
#ifdef __linux__
#define FACEDETECTDLL_API  
#else
#define FACEDETECTDLL_API __declspec(dllimport) 
#endif
#endif

FACEDETECTDLL_API int * facedetect_frontal( unsigned char * gray_image_data, int width, int height, int step, //input image, it must be gray (single-channel) image!
                               float scale, //scale factor for scan windows
                               int min_neighbors, //how many neighbors each candidate rectangle should have to retain it
                               int min_object_width, //Minimum possible face size. Faces smaller than that are ignored.
							   int max_object_width=0); //Maximum possible face size. Faces larger than that are ignored. It is the largest posible when max_object_width=0.

FACEDETECTDLL_API int * facedetect_multiview( unsigned char * gray_image_data, int width, int height, int step, //input image, it must be gray (single-channel) image!
                               float scale, //scale factor for scan windows
                               int min_neighbors, //how many neighbors each candidate rectangle should have to retain it
                               int min_object_width, //Minimum possible face size. Faces smaller than that are ignored.
							   int max_object_width=0); //Maximum possible face size. Faces larger than that are ignored. It is the largest posible when max_object_width=0.

FACEDETECTDLL_API int * facedetect_multiview_reinforce( unsigned char * gray_image_data, int width, int height, int step, //input image, it must be gray (single-channel) image!
                               float scale, //scale factor for scan windows
                               int min_neighbors, //how many neighbors each candidate rectangle should have to retain it
                               int min_object_width, //Minimum possible face size. Faces smaller than that are ignored.
							   int max_object_width=0); //Maximum possible face size. Faces larger than that are ignored. It is the largest posible when max_object_width=0.

FACEDETECTDLL_API int * facedetect_frontal_tmp( unsigned char * gray_image_data, int width, int height, int step, //input image, it must be gray (single-channel) image!
                               float scale, //scale factor for scan windows
                               int min_neighbors, //how many neighbors each candidate rectangle should have to retain it
                               int min_object_width, //Minimum possible face size. Faces smaller than that are ignored.
							   int max_object_width=0); //Maximum possible face size. Faces larger than that are ignored. It is the largest posible when max_object_width=0.

#endif
