INSERT INTO messages(id, chat_id, sender_id, reply_to_id, text, is_edited, created_at, updated_at)
VALUES (:id, :chat_id, :sender_id, :reply_to_id, :text, :is_edited, :created_at, :updated_at);
