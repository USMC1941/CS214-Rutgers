#!/bin/sh

# Sort by all keys!

make

cat movie_metadata.csv | ./sorter -c color > output_01_color.csv
cat movie_metadata.csv | ./sorter -c director_name > output_02_director_name.csv
cat movie_metadata.csv | ./sorter -c num_critic_for_reviews > output_03_num_critic_for_reviews.csv
cat movie_metadata.csv | ./sorter -c duration > output_04_duration.csv
cat movie_metadata.csv | ./sorter -c director_facebook_likes > output_05_director_facebook_likes.csv
cat movie_metadata.csv | ./sorter -c actor_3_facebook_likes > output_06_actor_3_facebook_likes.csv
cat movie_metadata.csv | ./sorter -c actor_2_name > output_07_actor_2_name.csv
cat movie_metadata.csv | ./sorter -c actor_1_facebook_likes > output_08_actor_1_facebook_likes.csv
cat movie_metadata.csv | ./sorter -c gross > output_09_gross.csv
cat movie_metadata.csv | ./sorter -c genres > output_10_genres.csv
cat movie_metadata.csv | ./sorter -c actor_1_name > output_11_actor_1_name.csv
cat movie_metadata.csv | ./sorter -c movie_title > output_12_movie_title.csv
cat movie_metadata.csv | ./sorter -c num_voted_users > output_13_num_voted_users.csv
cat movie_metadata.csv | ./sorter -c cast_total_facebook_likes > output_14_cast_total_facebook_likes.csv
cat movie_metadata.csv | ./sorter -c actor_3_name > output_15_actor_3_name.csv
cat movie_metadata.csv | ./sorter -c facenumber_in_poster > output_16_facenumber_in_poster.csv
cat movie_metadata.csv | ./sorter -c plot_keywords > output_17_plot_keywords.csv
cat movie_metadata.csv | ./sorter -c movie_imdb_link > output_18_movie_imdb_link.csv
cat movie_metadata.csv | ./sorter -c num_user_for_reviews > output_19_num_user_for_reviews.csv
cat movie_metadata.csv | ./sorter -c language > output_20_language.csv
cat movie_metadata.csv | ./sorter -c country > output_21_country.csv
cat movie_metadata.csv | ./sorter -c content_rating > output_22_content_rating.csv
cat movie_metadata.csv | ./sorter -c budget > output_23_budget.csv
cat movie_metadata.csv | ./sorter -c title_year > output_24_title_year.csv
cat movie_metadata.csv | ./sorter -c actor_2_facebook_likes > output_25_actor_2_facebook_likes.csv
cat movie_metadata.csv | ./sorter -c imdb_score > output_26_imdb_score.csv
cat movie_metadata.csv | ./sorter -c aspect_ratio > output_27_aspect_ratio.csv
cat movie_metadata.csv | ./sorter -c movie_facebook_likes > output_28_movie_facebook_likes.csv


cat movie_metadata.csv | ./sorter -r num_critic_for_reviews gross > correlation.txt
cat movie_metadata.csv | ./sorter -r duration gross >> correlation.txt
cat movie_metadata.csv | ./sorter -r director_facebook_likes gross >> correlation.txt
cat movie_metadata.csv | ./sorter -r actor_3_facebook_likes gross >> correlation.txt
cat movie_metadata.csv | ./sorter -r actor_1_facebook_likes gross >> correlation.txt
cat movie_metadata.csv | ./sorter -r gross gross >> correlation.txt
cat movie_metadata.csv | ./sorter -r num_voted_users gross >> correlation.txt
cat movie_metadata.csv | ./sorter -r cast_total_facebook_likes gross >> correlation.txt
cat movie_metadata.csv | ./sorter -r facenumber_in_poster gross >> correlation.txt
cat movie_metadata.csv | ./sorter -r num_user_for_reviews gross >> correlation.txt
cat movie_metadata.csv | ./sorter -r budget gross >> correlation.txt
cat movie_metadata.csv | ./sorter -r title_year gross >> correlation.txt
cat movie_metadata.csv | ./sorter -r actor_2_facebook_likes gross >> correlation.txt
cat movie_metadata.csv | ./sorter -r imdb_score gross >> correlation.txt
cat movie_metadata.csv | ./sorter -r aspect_ratio gross >> correlation.txt
cat movie_metadata.csv | ./sorter -r movie_facebook_likes gross >> correlation.txt

