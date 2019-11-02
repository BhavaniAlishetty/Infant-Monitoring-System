import cv2
import numpy as np

def get_output_layers(net):
    
    layer_names = net.getLayerNames()
    
    output_layers = [layer_names[i[0] - 1] for i in net.getUnconnectedOutLayers()]

    return output_layers

classes = "C:/Users/RamyaV/Downloads/Mini project/MiniProject/Mini/object_detection/yolov3.txt"
weights = "C:/Users/RamyaV/Downloads/Mini project/MiniProject/Mini/object_detection/yolov3.weights"
config =  "C:/Users/RamyaV/Downloads/Mini project/MiniProject/Mini/object_detection/yolov3.cfg"
with open(classes, 'r') as f:
   classes = [line.strip() for line in f.readlines()]
net = cv2.dnn.readNet(weights, config)

def object_detect_function():
    raw_image = "C:/Users/RamyaV/Downloads/Mini project/MiniProject/Mini/object_detection/Motion Pictures.jpg"  ##Change the code here to Motion_Picture.jpg
    image = cv2.imread(raw_image)
    Width = image.shape[1]
    Height = image.shape[0]
    scale = 0.00392
    blob = cv2.dnn.blobFromImage(image, scale, (416,416), (0,0,0), True, crop=False)
    net.setInput(blob)
    outs = net.forward(get_output_layers(net))
    class_ids = []
    confidences = []
    boxes = []

    for out in outs:
        for detection in out:
            scores = detection[5:]
            class_id = np.argmax(scores)
            confidence = scores[class_id]
            if confidence > 0.5:
                center_x = int(detection[0] * Width)
                center_y = int(detection[1] * Height)
                w = int(detection[2] * Width)
                h = int(detection[3] * Height)
                x = center_x - w / 2
                y = center_y - h / 2
                class_ids.append(class_id)
                confidences.append(float(confidence))
                boxes.append([x, y, w, h])

    detected_objects=[]
    detected_objects=[classes[index] for index in class_ids]
    return detected_objects



