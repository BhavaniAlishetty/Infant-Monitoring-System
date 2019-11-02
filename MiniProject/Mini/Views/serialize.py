from rest_framework.decorators import api_view
from rest_framework.response import *
from rest_framework import status
from Mini.object_detection.yolo_opencv import *

@api_view(['GET', 'POST'])

def Create_Response(request, *args, **kwargs):
    detected_objects=object_detect_function()
    if request.method == 'GET':
        print(detected_objects)
        if "person" in detected_objects:
            return Response({'Message':'person','Status':1})
        return Response({'Message':'no person','Status':0}, status=status.HTTP_400_BAD_REQUEST)
    return Response({'Message':'Error'}, status=status.HTTP_400_BAD_REQUEST)










    # if request.method == 'POST':
    #     serializer = CollegeSerializer(data=request.data)
    #     if serializer.is_valid():
    #         serializer.save()
    #         return Response(serializer.data, status=status.HTTP_201_CREATED)
    #     return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

