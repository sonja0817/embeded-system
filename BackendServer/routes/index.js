const express = require('express');
const Post =require('../models/post');
const router = express.Router();
router.get('/', async (req, res, next) => {
  try {
    const posts = await Post.findAll();
    res.render('sequelize', { posts });
  } catch (err) {
    console.error(err);
    next(err);
  }
});


module.exports = router;
