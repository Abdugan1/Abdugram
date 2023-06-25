SELECT c.*
FROM chats c
JOIN chat_users cu ON c.id = cu.chat_id
WHERE  cu.user_id = :user_id
AND c.updated_at >= :last_updated_at;
