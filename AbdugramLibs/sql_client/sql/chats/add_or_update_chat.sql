INSERT OR REPLACE INTO chats(id, name, description, type, created_at, updated_at, deleted_at) 
VALUES(:id, :name, :description, :type, :created_at, :updated_at, :deleted_at);
