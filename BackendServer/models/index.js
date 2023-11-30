const Sequelize = require('sequelize');
const Post=require('./post');
const env = process.env.NODE_ENV || 'development';
const config = require('../config/config')[env];
const db = {};
const sequelize = new Sequelize(config.database, config.username, config.password, config);

db.sequelize = sequelize;
db.Post=Post;
Post.init(sequelize);

module.exports = db;
