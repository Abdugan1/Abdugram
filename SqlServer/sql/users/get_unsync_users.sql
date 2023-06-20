SELECT u.*
FROM users u
JOIN chat_users cu ON cu.user_id = u.id
JOIN chats c ON c.id = cu.chat_id
WHERE c.id IN (
    SELECT chat_id
    FROM chat_users
    WHERE user_id = :user_id
)
AND u.updated_at >= :last_updated_at;
