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
      const posts = await Post.create({
        location: req.body.location,
        peopleNum:req.body.peopleNum,
        congestion:req.body.congestion,
        date:req.body.date,
        image:req.body.image,
    });
      console.log(posts);
      res.status(201).json(posts);
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
        model: Post, // 관련된 모델을 지정
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
