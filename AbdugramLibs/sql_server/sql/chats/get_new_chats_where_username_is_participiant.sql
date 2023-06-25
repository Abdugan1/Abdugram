SELECT * FROM chats
JOIN participants ON chats.id = participants.chat_id
JOIN users ON participants.user_id = users.id
WHERE users.username = :username AND chats.updated_at > :last_update;
