# Example Python Code to Insert a Document 

#Added import for errors from pymongo
from pymongo import MongoClient, errors
from bson.objectid import ObjectId 
#For converting cursor object to string.
from bson.json_util import dumps 

class AnimalShelter(object): 
    """ CRUD operations for Animal collection in MongoDB """ 

    def __init__(self, username, password): 
        # Initializing the MongoClient. This helps to access the MongoDB 
        # databases and collections. This is hard-wired to use the aac 
        # database, the animals collection, and the aac user. 
        # 
        # You must edit the password below for your environment. 
        # 
        # Connection Variables 
        # 
        USER = 'aacuser' 
        PASS = 'CS340Pass' 
        HOST = 'localhost' 
        PORT = 27017 
        DB = 'aac' 
        COL = 'animals' 
        # 
        # Initialize Connection 
        # 
        # Here I replaced the old C style formatting with native Python f strings.
        self.client = MongoClient(f"mongodb://{USER}:{PASS}@{HOST}:{PORT}")
        self.database = self.client[DB]
        self.collection = self.database[COL]

    # Create a method to return the next available record number for use in the create method
            
    # Complete this create method to implement the C in CRUD. 
    def create(self, data):
        if data:
            try:
                self.database.animals.insert_one(data)
                return True
            except errors.PyMongoError:
                return False
        return False 

    # Create method to implement the R in CRUD.
    #I added try and except blocks to prevent crashes by catching errors during reading
    def read(self, dataSearch):
        try:
            if dataSearch is not None:
                data = self.collection.find(dataSearch, {"_id": False})
            else:
                data = self.collection.find({}, {"_id": False})
            return data
        except errors.PyMongoError as e:
            print(f"Database error during read: {e}")
            return None
    
    # Create method to implement the U in CRUD.
    #I wrapped the operation in a try and except block to catch any errors.
    def update(self, dataSearch, dataUpdate):
        #I made sure dataUpdate is not None as well as dataSearch. 
        if dataSearch is not None and dataUpdate is not None:
            try:
                # Searching current data and setting the new updates
                result = self.collection.update_many(dataSearch, {"$set": dataUpdate})
                return result
            except errors.PyMongoError as e:
                print(f"Database error during update: {e}")
                return None
        else:
            return "{}"
            
    # Create method to implement the D in CRUD.
    #I wrapped the operation in a try and except block to catch any errors.
    def delete(self, dataDelete):
        if dataDelete is not None:
            try:
                result = self.collection.delete_many(dataDelete)
                return result
            except errors.PyMongoError as e:
                print(f"Database error during delete: {e}")
                return None
        else:
            return "{}"
    
