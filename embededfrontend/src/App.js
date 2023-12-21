import './App.css';
import Viewpost from './Viewpost';
import Main from './Main';
import { BrowserRouter, Routes, Route, Link} from 'react-router-dom';
import React from 'react';
 function App() {
  return (
    <BrowserRouter>
    <div className="App">
          <Routes>
              <Route path="/*" element={<Main />}></Route> 
              <Route path="/Main/*" element={<Main />}></Route>
              <Route path="/Viewpost" element={<Viewpost />}></Route>
         </Routes>
    </div>
    </BrowserRouter>
  );
}

export default App;
