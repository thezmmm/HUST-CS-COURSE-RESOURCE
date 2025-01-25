-- 生成user表示例数据
INSERT INTO user (user_id, user_name, password, level, register_date, login_date)
VALUES ('1', 'John', 'password123', 1, '2023-01-01', '2023-01-02'),
('2', 'Jane', 'pass456', 2, '2023-01-03', '2023-01-04'),
('3', 'Mike', 'qwerty', 1, '2023-02-05', '2023-02-06'),
('4', 'Emily', 'abc123', 3, '2023-02-10', '2023-02-11'),
('5', 'David', 'p@ssw0rd', 2, '2023-03-15', '2023-03-16'),
('6', 'Sarah', 'hello123', 1, '2023-04-20', '2023-04-21'),
('7', 'Ryan', 'welcome', 2, '2023-05-25', '2023-05-26'),
('8', 'Olivia', 'sunshine', 3, '2023-06-30', '2023-07-01'),
('9', 'Daniel', 'letmein', 1, '2023-08-05', '2023-08-06'),
('10', 'Sophia', 'password1', 2, '2023-09-10', '2023-09-11');

-- 生成post示例数据
INSERT INTO post (post_id, post_title, post_content, post_date, post_like, user_id)
VALUES ('1', 'Exciting Trip to the Beach', 'I had an amazing time at the beach today! The weather was perfect, and I enjoyed swimming in the clear blue water. Cant wait to go back!', '2023-01-05', 10, '1'),
('2', 'Delicious Homemade Pizza Recipe', 'I just tried a new pizza recipe and it turned out fantastic! The crust was crispy, and the toppings were so flavorful. I highly recommend giving it a try!', '2023-01-06', 5, '2'),
('3', 'Hiking Adventure in the Mountains', 'Spent the weekend hiking in the beautiful mountains. The scenery was breathtaking, and I even saw some wildlife along the way. It was an unforgettable experience!', '2023-02-07', 8, '3'),
('4', 'Book Recommendation: "The Great Gatsby"', 'I recently finished reading "The Great Gatsby" by F. Scott Fitzgerald, and it blew me away. The story is captivating, and the writing is exquisite. Definitely a must-read!', '2023-02-08', 3, '4'),
('5', 'Exciting New Tech Gadgets', 'Just got my hands on the latest tech gadgets, and they are incredible! The new features and performance upgrades are mind-blowing. It is like living in the future!', '2023-03-10', 12, '5'),
('6', 'Delicious Chocolate Cake Recipe', 'I baked a chocolate cake today, and it turned out to be a piece of heaven! The cake was moist, and the chocolate ganache frosting was divine. It is a recipe worth sharing!', '2023-04-12', 7, '6'),
('7', 'Movie Recommendation: "Inception"', 'If you havent seen "Inception" yet, you are missing out! Its a mind-bending thriller with stunning visuals and an intriguing storyline. Prepare to have your mind blown!', '2023-05-15', 2, '7'),
('8', 'Amazing Music Concert Experience', 'Attended a music concert last night, and it was absolutely amazing! The energy, the atmosphere, and the performances were all top-notch. It was a night to remember!', '2023-06-18', 9, '8'),
('9', 'Travel Destination: Bali', 'Just came back from a trip to Bali, and it was paradise on earth. The beaches, the temples, and the local culture were all incredible. I cant wait to go back again!', '2023-08-20', 6, '9'),
('10', 'Delicious Sushi Experience', 'Tried a new sushi restaurant yesterday, and it was a delightful culinary experience. The sushi was fresh, beautifully presented, and bursting with flavors. Sushi lovers, you have to try it!', '2023-09-23', 4, '10');

-- 生成comment示例数据
INSERT INTO comment (comment_id, post_id, comment_content, comment_date, comment_like, user_id)
VALUES ('1', '1', 'Sounds like you had an amazing day at the beach! I love swimming too, especially in clear blue water. Cant wait for summer!', '2023-01-07', 3, '2'),
('2', '2', 'Your homemade pizza looks delicious! Would you mind sharing the recipe? I am always on the lookout for new pizza ideas.', '2023-01-08', 1, '1'),
('3', '3', 'Hiking in the mountains is one of my favorite activities. The scenery is indeed breathtaking. Any tips for a beginner hiker?', '2023-02-09', 2, '3'),
('4', '4', 'I agree, "The Great Gatsby" is a masterpiece! The story is so captivating, and the characters are fascinating. Have you read any other books by F. Scott Fitzgerald?', '2023-02-10', 5, '4'),
('5', '5', 'I am a tech enthusiast too! What are the new gadgets you got? I am always interested in the latest tech innovations.', '2023-03-12', 1, '5'),
('6', '6', 'Your chocolate cake looks divine! Would you mind sharing the recipe? I am a big fan of chocolate desserts.', '2023-04-15', 4, '6'),
('7', '7', '"Inception" is one of my all-time favorite movies! The concept is mind-blowing, and the visuals are stunning. Christopher Nolan is a genius.', '2023-05-18', 7, '7'),
('8', '8', 'I love attending music concerts! Which artists performed at the concert you went to? I am always looking for new music recommendations.', '2023-06-21', 2, '8'),
('9', '9', 'Bali is on my travel bucket list! Any must-visit places or recommendations for things to do?', '2023-08-25', 3, '9'),
('10', '10', 'Your sushi pictures are making me hungry! I am a sushi lover too. Can you share the name of the sushi restaurant?', '2023-09-28', 6, '10'),
('11', '1', '"Inception" is one of my all-time favorite movies! The concept is mind-blowing, and the visuals are stunning. Christopher Nolan is a genius.', '2023-05-18', 7, '7'),
('12', '2', 'I love attending music concerts! Which artists performed at the concert you went to? I am always looking for new music recommendations.', '2023-06-21', 2, '8'),
('13', '3', 'Bali is on my travel bucket list! Any must-visit places or recommendations for things to do?', '2023-08-25', 3, '9'),
('14', '4', 'Your sushi pictures are making me hungry! I am a sushi lover too. Can you share the name of the sushi restaurant?', '2023-09-28', 6, '10'),
('15', '1', 'I totally agree! Swimming in clear blue water is such a refreshing experience. I cant wait for summer either!', '2023-01-10', 2, '3'),
('16', '2', 'Your pizza looks amazing! I would love to try your recipe. Pizza is my all-time favorite comfort food.', '2023-01-11', 4, '5'),
('17', '3', 'For beginner hikers, I would recommend starting with shorter trails and gradually increasing the difficulty. Dont forget to pack enough water and wear comfortable shoes!', '2023-02-12', 3, '2'),
('18', '1', 'Yes, "The Great Gatsby" is a masterpiece indeed. Fitzgerald is writing style is so elegant and the way he captures the Jazz Age is remarkable.', '2023-02-15', 6, '7'),
('19', '2', 'I recently got the latest smartphone model and a new smartwatch. They have some cool features and I am really enjoying them!', '2023-03-18', 2, '4');