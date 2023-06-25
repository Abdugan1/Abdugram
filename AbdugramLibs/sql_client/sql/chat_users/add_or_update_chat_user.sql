INSERT OR REPLACE INTO chat_users(chat_id, user_id, role, joined_at, left_at, updated_at)
VALUES (:chat_id, :user_id, :role, :joined_at, :left_at, :updated_at);
