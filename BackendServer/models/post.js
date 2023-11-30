const Sequelize = require('sequelize');

module.exports = class User extends Sequelize.Model {
  static init(sequelize) {
    return super.init({
      location: {
        type: Sequelize.STRING(20),
        allowNull: false,
        
      },
      peopleNum: {
        type: Sequelize.STRING(30),
        allowNull: false,
        
      },
      congestion: {
        type: Sequelize.STRING(30),
        allowNull: false,
        
      },
      date: {
        type: Sequelize.STRING(10),
        allowNull: false,
       
      },
      image: {
        type: Sequelize.TEXT('medium'),
        allowNull: true,
       
      }
    }, {
      sequelize,
      timestamps: false,
      underscored: false,
      modelName: 'Post',
      tableName: 'posts',
      paranoid: false,
      charset: 'utf8',
      collate: 'utf8_general_ci',
    });
  }

  
};
