import React, { useState, useEffect,callback,useCallback,useRef } from 'react';
import './Viewpost.css';
import { useNavigate,useLocation } from "react-router-dom";
import Header from './Header';
export const Viewpost=(props)=>{
    const location = useLocation();
    const location1=location.state.location;
    const congestion=location.state.congestion;
    const image=location.state.image;
    const date=location.state.date;
    const image1=location.state.image1;
    const image2=location.state.image2;
    const image3=location.state.image3;
    useEffect(()=>{
    },[])
    const navigate = useNavigate();
    const id=location.state.id;
      const now=new Date();
  return (
    <div className="Viewpost">
    <Header/>
     <div className="Viewpost2">
        <div className="Viewpost3">
            <br></br><br></br>
            <div className='gridview'>
              <div className="post3"></div>
             <div className='rightbar'><div></div>
            </div>
            </div>
            <div className='post1'>
            <br></br>
            <div className='title'> {location1}<br></br></div>
            <br></br>
            <div className='bar'>{date}<br></br>혼잡도: {congestion}<br></br></div>
            <br></br> <img src={image} className="postimage"/>
 <img src={image1} className="postimage"/>
 <img src={image2} className="postimage"/>
 <img src={image3} className="postimage"/>
 <div className="contentname"></div>
 <br></br> </div> <br></br>  <br></br>{/* <button onClick={deletepost} className="delbutton">삭제하기</button>*/}
         <div className='post2'><br></br></div>
    </div></div>
</div>

  );
}
export default Viewpost;