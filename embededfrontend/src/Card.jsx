import React, { useState } from "react";
import './Card.css';
import peopleNumimg from'./imgs/peopleNum.png';
import time from './imgs/time.png';
import { Navigate, useNavigate } from "react-router-dom";
const Card=(props)=>{
  const navigate=useNavigate();
  const date=props.date;
  const id=props.id;
  const location=props.location
  const peopleNum=props.peopleNum
  const congestion=props.congestion
  const image=props.image
  const image1=props.image1
  const image2=props.image2
  const image3=props.image3
    function gotoViewpost(){
      navigate('/Viewpost',{state : {
      id:id,
      date:date,
      location:location,
      congestion:congestion,
      image:image,
      image1:image1,
      image2:image2,
      image3:image3
      }});
    }
  return(
                 <div className="Card" >
                  <div className="cardbody">
                  <div className="vh2"></div>
                  <div className="info">{props.location}</div>
                  <div className="subinfo">
                  <div className="vh2"></div>
                  <img src={time}/> {props.date}</div>
                  <div className="attendmessage">혼잡도: {props.congestion}  <button className="viewbutton"onClick={gotoViewpost}>자세히보기</button></div>
                  <br></br> 
                  </div>
                </div>
  )
};
export default Card;