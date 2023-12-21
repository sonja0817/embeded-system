
import './Main.css';
import Header from"./Header";
import axios from 'axios';
import React, { useState, useEffect,callback,useCallback,useRef } from 'react';
import Card from './Card';
function Main() {
  const [posts,setPosts]=useState([]);
  const getPosts=()=>{
    axios.get('/posts/').then((res)=>{
        if(regionset==''){
          setPosts(res.data.filter(function(e){
        return (e.congestion.includes(searchText));}))}
        if(regionset=='1'){
          setPosts(res.data.filter(function(e){
          return (e.congestion.includes(searchText))&&e.congestion.includes('1');
        }))}
        if(regionset=='2'){
          setPosts(res.data.filter(function(e){
          return (e.congestion.includes(searchText))&&e.congestion.includes('2');
        }))}
        if(regionset=='3'){
          setPosts(res.data.filter(function(e){
          return (e.congestion.includes(searchText))&&e.congestion.includes('3');
        }))}
        if(regionset=='4'){
          setPosts(res.data.filter(function(e){
          return (e.congestion.includes(searchText))&&e.congestion.includes('4');
        }))}
        if(regionset=='5'){
          setPosts(res.data.filter(function(e){
          return (e.congestion.includes(searchText))&&e.congestion.includes('5');
        }))}
        if(regionset=='6'){
          setPosts(res.data.filter(function(e){
          return (e.congestion.includes(searchText))&&e.congestion.includes('6');
        }))}
        if(regionset=='7'){
          setPosts(res.data.filter(function(e){
          return (e.congestion.includes(searchText))&&e.congestion.includes('7');
        }))}
        if(regionset=='8'){
          setPosts(res.data.filter(function(e){
          return (e.congestion.includes(searchText))&&e.congestion.includes('8');
        }))}
        if(regionset=='0'){
          setPosts(res.data.filter(function(e){
          return (e.congestion.includes(searchText))&&e.congestion.includes('0');
        }))}
     
    })
  }
  useEffect(()=>{
    getPosts();
  },[]);
  const[searchText,setSearchText]=useState('');
  const onSearch=()=>{
    getPosts();
  }
  const [regionset, setRegion] = useState('');
  const handleSelect2 = (e) => {
    setRegion(e.target.value);
  };
  const [,updateState]=useState();
  const forceUpdate=useCallback(()=>updateState({}),[]);
    
    console.log(regionset);

   let countsetting=6;
   let postcounter=0;
   function reset(){
    setcounter(countsetting);
    forceUpdate();
   }
   const [count,setcounter]=useState(6);  //한번에 6게시글씩보기
  return (
    <div className="Main">
      <Header/>
      <div className="Main2">
           <br></br><br></br><br></br>
           <input 
            onKeyDown={(e)=>setSearchText(e.target.value)}
            onKeyUp={getPosts}
            className="search" type="text" placeholder="원하시는 혼잡도만 찾아보세요 (입력후 엔터)"/>
            <br></br>
             <div className="gridtop">
          <select onChange={handleSelect2} value={regionset} id="region" className="inputgenderset">
                <option  value='' >전체혼잡도</option>
                <option  value='0' >혼잡도 0</option>
                <option  value='1'>혼잡도 1</option>
                <option  value='2'>혼잡도 2</option>
                <option  value='3'>혼잡도 3</option>
                <option  value='4' >혼잡도 4</option>
                <option  value='5' >혼잡도 5</option>
                <option  value='6' >혼잡도 6</option>
                <option  value='7' >혼잡도 7</option>
                <option  value='8' >혼잡도 8</option>
            </select>
            <button className="submit" onClick={getPosts}>적용</button>
            </div>
           <br></br>
            <div className="grid">
              {posts.map(post=>{
                if(postcounter==count){
                 return;
                }
                else{
                  countsetting++;
                }
                postcounter++;
                return (
                  <Card
                  id={post.id} 
                  location={post.location}
                  peopleNum={post.peopleNum}
                  congestion={post.congestion}
                  date={post.date}
                  image={'data:image/jpeg;base64,'+post.image}
                  image1={'data:image/jpeg;base64,'+post.image1}
                  image2={'data:image/jpeg;base64,'+post.image2}
                  image3={'data:image/jpeg;base64,'+post.image3}
                  />
                );
              })}
            </div>
              <button className="submit2" onClick={reset}>더보기</button>
       </div>   
      
    </div>
  );
}

export default Main;