import os
import socket
from flask import Flask, Response, request, jsonify, make_response
from dotenv import load_dotenv
from pymongo import MongoClient
from bson.json_util import dumps
from bson.objectid import ObjectId

load_dotenv()


hostname = socket.gethostname()
local_ip = socket.gethostbyname(hostname)
app = Flask(__name__)
mongo_db_url = os.environ.get("MONGO_DB_CONN_STRING")

client = MongoClient(mongo_db_url)
db = client['ID_db']

@app.get("/api/ID")
def get_product():
    ID = request.args.get('ID')
    filter = {} if ID is None else {"ID": ID}
    ID = list(db.ID.find(filter))

    response = Response(
        response=dumps(ID), status=200,  mimetype="application/json")
    return response

@app.post("/api/ID")
def add_product():
    _json = request.json
    db.ID.insert_one(_json)

    resp = jsonify({"message": "ID added successfully"})
    resp.status_code = 200
    return resp


@app.delete("/api/ID/<id>")
def delete_product(id):
    # Find and delete the product based on the product ID field
    result = db.ID.delete_one({'product.ID': id})

    if result.deleted_count > 0:
        resp = jsonify({"message": "Product deleted successfully"})
        resp.status_code = 200
    else:
        resp = jsonify({"message": "Product not found"})
        resp.status_code = 404

    return resp

@app.put("/api/ID/<id>")
def update_product(id):
    _json = request.json
    db.ID.update_one({'product.ID': id}, {"$set": _json})

    resp = jsonify({"message": "Sensor updated successfully"})
    resp.status_code = 200
    return resp

@app.errorhandler(400)
def handle_400_error(error):
    return make_response(jsonify({"errorCode": error.code, 
                                  "errorDescription": "Bad request!",
                                  "errorDetailedDescription": error.description,
                                  "errorName": error.name}), 400)

@app.errorhandler(404)
def handle_404_error(error):
        return make_response(jsonify({"errorCode": error.code, 
                                  "errorDescription": "Resource not found!",
                                  "errorDetailedDescription": error.description,
                                  "errorName": error.name}), 404)

@app.errorhandler(500)
def handle_500_error(error):
        return make_response(jsonify({"errorCode": error.code, 
                                  "errorDescription": "Internal Server Error",
                                  "errorDetailedDescription": error.description,
                                  "errorName": error.name}), 500)