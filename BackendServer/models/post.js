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
        allowNull: true,
        
      },
      date: {
        type: Sequelize.STRING(20),
        allowNull: true;,
       
      },
      image: {
        type: Sequelize.TEXT('medium'),
        allowNull: true,
      },
      image1: {
        type: Sequelize.TEXT('medium'),
        allowNull: true,
       
      },
       image2: {
        type: Sequelize.TEXT('medium'),
        allowNull: true,
       
      },
       image3: {
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
