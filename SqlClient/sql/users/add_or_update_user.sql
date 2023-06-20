INSERT OR REPLACE INTO users(id, username, first_name, last_name, email, phone, avatar_url, is_online, last_time_online, url_to_profile, created_at, updated_at, deleted_at)
VALUES(:id, :username, :first_name, :last_name, :email, :phone, :avatar_url, :is_online, :last_time_online, :url_to_profile, :created_at, :updated_at, :deleted_at);
