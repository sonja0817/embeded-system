import cv2
import base64
import requests
import json
import datetime
import os
capture=cv2.VideoCapture(2)
previous_frame=None
count=0
while True:
	ret, frame=capture.read()
	if not ret:
		print("no webcam")
		break
	gray=cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
	if previous_frame is not None:
		frame_diff=cv2.absdiff(previous_frame,gray)
		threshold=30
		_, frame_threshold=cv2.threshold(frame_diff,threshold,255,cv2.THRESH_BINARY)
		contours, _=cv2.findContours(frame_threshold.copy(), cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
		for contour in contours:
			if cv2.contourArea(contour)>100:
				x,y,w,h=cv2.boundingRect(contour)
				x,y,w,h=int(x),int(y),int(w),int(h)
				cv2.rectangle(frame,(x,y),(x+w,y+h),(0,255,0),2)
				count=count+1
		print("boxcount:",count)
	previous_frame=gray.copy()
	cv2.imshow("webcam",frame)
	if count>2:
		try:
			if count>25:
				congestion="8"
			elif count>20:
				congestion="7"
			elif count>15:
				congestion="6"
			elif count>10:
				congestion="5"
			elif count>8:
				congestion="4"
			elif count>6:
				congestion="3"
			elif count>4:
				congestion="2"
			elif count>2:
				congestion="1"
			
			current_directory=os.getcwd()
			file_path=os.path.join(current_directory,'congestion.txt')
		#	with open(file_path,'r+')as file:
		#		content=file.read()
		#		file.seek(0)
		#		file.write(congestion)
				#file.write(content)
		#	_,img_encoded=cv2.imencode('.jpg',frame)
		#	img_base64=base64.b64encode(img_encoded)
		#	url='http://embeded.site:3002/posts/1'
		#	data={
		#		'location':"MYONGJI_UNIV_Y19122",
		#		'peopleNum':"UNKNWON",
		#		'congestion':congestion,
		#		'date':datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S'),
		#		'image':img_base64}
		#	headers={'Content-Type':'application/json'}
		#	response=requests.put(url,data=json.dumps(data),headers=headers)
		#	print(response.status_code)
		except Exception as e:
			print(e)
	count=0
	if cv2.waitKey(1)&0xFF==ord('q'):
		break
capture.release()
cv2.destroyAllWindows()
