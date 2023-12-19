
import base64
import requests
import json
import datetime
import os
import time
congestion=5
check='0'
while True:
	time.sleep(1)                                      #1초마다 버튼이눌렸는지 check.txt의 첫숫자를 보고 검사함 
		
	try:			
		print('checkopening')
		with open('check.txt','r')as file:             #check.txt파일을 열어서 첫글자를 읽어옴
			cont ent=file.read()
		check=content[0]
		print('readcheck:',check)
		
		if check=='1':                            #읽어온 첫문자가 1일시에 if문진입
			print('check=1ifstart')
			with open('check.txt','w')as file:        #먼저 check.txt파일에 다시 0을 작성함
				file.write('0')

			with open('congestion.txt','r')as file:   #congestion.txt 혼잡도를 기록한 파일을 열어서 혼잡도1~8을 읽어옴
				congestion_content=file.read()
			congestion=congestion_content[0]

			with open('Coin1.jpg','rb')as file:                           #이미지1을 열어서 base64문자열변환
				img_encoded=file.read()	
				img_base64_c=base64.b64encode(img_encoded)

			with open('Coin2.jpg','rb')as file:                        #이미지2를 열어서 base64문자열변환
                       		img_encoded=file.read()
	                        img_base64_1_c=base64.b64encode(img_encoded)
	
			with open('Coin3.jpg','rb')as file:                     #이미지3을 열어서 base64문자열변환
        	                img_encoded=file.read()
                	        img_base64_2_c=base64.b64encode(img_encoded)
	
			with open('Coin4.jpg','rb')as file:                       #이미지4를 열어서 base64문자열변환
        	                img_encoded=file.read()
                	        img_base64_3_c=base64.b64encode(img_encoded)

			url='http://embeded.site:3002/posts'                         #API URL
			data={                                                     #JSON DATA생성
				'location':"MYONGJI_UNIV_Y19122",
				'peopleNum':"UNKNWON",
				'congestion':congestion,
				'date':"0",
				'image':img_base64_c,
				'image1':img_base64_1_c,
				'image2':img_base64_2_c,
				'image3':img_base64_3_c
				}
			headers={'Content-Type':'application/json'}       #헤더 선언

			response=requests.post(url,data=json.dumps(data),headers=headers)  #POST요청
			print('response:',response)                                         #POST RESPONSE출력
	
	except Exception as e:                          #예외
		print(e)
