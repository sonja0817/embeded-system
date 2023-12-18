
import base64
import requests
import json
import datetime
import os
import time
congestion=5
check='0'
while True:
	time.sleep(2)
		
	try:			
		print('checkopening')
		with open('check.txt','r')as file:
			content=file.read()
		check=content[0]
		print('readcheck:',check)
		
		if check=='1':
			print('check=1ifstart')
			with open('check.txt','w')as file:
				file.write('0')
			with open('Coin1.jpg','rb')as file:
				img_encoded=file.read()	
				img_base64_c=base64.b64encode(img_encoded)
			with open('Coin2.jpg','rb')as file:
                       		img_encoded=file.read()
	                        img_base64_1_c=base64.b64encode(img_encoded)
	
			with open('Coin3.jpg','rb')as file:
        	                img_encoded=file.read()
                	        img_base64_2_c=base64.b64encode(img_encoded)
	
			with open('Coin4.jpg','rb')as file:
        	                img_encoded=file.read()
                	        img_base64_3_c=base64.b64encode(img_encoded)

			url='http://embeded.site:3002/posts'
			data={
				'location':"MYONGJI_UNIV_Y19122",
				'peopleNum':"UNKNWON",
				'congestion':congestion,
				'date':"0",
				'image':img_base64_c,
				'image1':img_base64_1_c,
				'image2':img_base64_2_c,
				'image3':img_base64_3_c
				}
			headers={'Content-Type':'application/json'}

			response=requests.post(url,data=json.dumps(data),headers=headers)
			print('response:',response)
	
	except Exception as e:
		print(e)
