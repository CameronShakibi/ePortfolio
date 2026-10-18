# Example Python Code to Insert a Document 

from pymongo import MongoClient 
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
        self.client = MongoClient('mongodb://%s:%s@%s:%d' % (USER,PASS,HOST,PORT)) 
        self.database = self.client['%s' % (DB)] 
        self.collection = self.database['%s' % (COL)] 

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
    def read(self, dataSearch):
        if dataSearch is not None:
           data = self.database.animals.find(dataSearch, {"_id": False})
        else:
            data = self.database.animals.find( {}, {"_id": False})
        #return dumps(data)
        return data
    
    # Create method to implement the U in CRUD.
    def update(self, dataSearch, dataUpdate):
        if dataSearch is not None:
            #Searching the current data and setting the new update to that item.
            result = self.database.animals.update_many(dataSearch, { "$set": dataUpdate})
        else:
            return "{}"
        return result
            
    # Create method to implement the D in CRUD.
    def delete(self, dataDelete):
        if dataDelete is not None:
            result = self.database.animals.delete_many(dataDelete)
        else:
            return "{}"
        return result 
    
