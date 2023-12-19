const express = require('express');
const Post = require('../models/post');
const router = express.Router();

router.route('/')
  .get(async (req, res, next) => {
    try {
      const posts = await Post.findAll();
      res.json(posts);
    } catch (err) {
      console.error(err);
      next(err);
    }
  })
  .post(async (req, res, next) => {
    try {
        let year=new Date().getFullYear();
        let month=new Date().getMonth()+1;
        let date=new Date().toLocaleString('en-US',{timeZone:'Asia/Seoul',day:'numeric'});
        let hours=new Date().toLocaleString('en-US',{timeZone:'Asia/Seoul',hour:'numeric'}).slice(0,-3);
        let minutes=new Date().toLocaleString('en-US',{timeZone:'Asia/Seoul',minute:'numeric'});
        let currentdate=year+'/'+month+'/'+date+' '+hours+':'+minutes;
      const posts = await Post.create({
        location: req.body.location,
        peopleNum:req.body.peopleNum,
        congestion:req.body.congestion,
        date:currentdate,
        image:req.body.image,
        image1:req.body.image1,
        image2:req.body.image2,
        image3:req.body.image3
    });
      res.status(200).json({message:'success');
    } catch (err) {
      console.error(err);
      next(err);
    }
  });
  

router.route('/:location')
  
  .delete(async (req, res, next) => {
    try {
      const result = await Post.destroy({ where: { location: req.params.location } });
      res.json(result);
    } catch (err) {
      console.error(err);
      next(err);
    }
  });
router.route('/:location')
  .get(async (req, res, next) => {
    try {
      const posts = await Post.findAll({
        model: Post, 
         where: { location: req.params.location },
      });
      console.log(posts);
      res.json(posts);
    } catch (err) {
      console.error(err);
      next(err);
    }
  });
  router.route('/:location')
  .put(async (req, res, next) => {
    try {
      const result = await Post.update({
      }, {
        model:Post,
        where: { location: req.params.location },
      });
      res.json(result);
    } catch (err) {
      console.error(err);
      next(err);
    }
  })
  

module.exports = router;
