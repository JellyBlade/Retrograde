# Retrograde Command Processor (RGScript)
- What is it?
  - Retrograde's Command Processor allows you to use specific keywords in any of the game's text to create conditional (if) and branching (mc) dialogue, and perform in-game actions, such as moving players/npcs, giving items to the player, blocking/unblocking doors, etc.
- How does it work?
  - The Command Processor is called whenever TextHelper::readFile() encounters a line that starts with `:`. From there, the rest of the line may be used to specify parameters for the different commands.
- What are the commands?
  - Read the next section :)
# Command Processor Commands
### Comments
- Not really a command per se, but any line that starts with `/` or `//` will not be output or processed.
	- `// this is a comment`
### Line Spacing
- Command  Processor will trim any whitespace from the front/end before performing commands.
- This lets you add tabs/spaces to commands, which is helpful for the readability of nested commands.
- <details>
	<summary><b>Example Usage:</b></summary>
	<pre><code>
	:if spacesuit
		Spacesuit!
		:if holding oxygen tank
		Oxygen Tank!
			:if holding apple
			Apple!
			:endif
		:endif
	:endif
	</pre></code>
## Conditional Dialogue
### :if & :else
- `:if` allows for conditional dialogue based on specific criteria that have to be met in order for the lines inside of the if-block to be displayed.
- `:else` lets you specify an alternative block of text to be read if the criteria is false.
- **The :if block requires a matching :endif tag at the end of the block!**
- <details>
	 <summary><b>Example Usage:</b></summary>
	  <pre><code>
	  :if holding apple
	  This line will only appear if the player has an apple in their inventory!
	  :else
	  This line will only appear if the player does not have an apple in their inventory.
	  :endif
	  </code></pre>
	</details>

- `:if` criteria list
	- `spacesuit`
		- `:if spacesuit`
		- Only true if the player has the spacesuit.
		- <details>
			<summary><b>Example Usage:</b></summary>
			 <pre><code>
			 Joe: Do you have the spacesuit yet?
			 :if spacesuit
			 Joe: You've got the spacesuit! Nice!
			 :else
			 Joe: You need to get the spacesuit still! It's over in that airlock.
			 Come back to me once you've got it.
			 :endif
			 </code></pre></details>
	- `holding`
		- `:if holding [name of object]`
		- Only true if the player has that object in their inventory.
		- The object name can include spaces and punctuation.
		- <details>
			<summary><b>Example Usage:</b></summary>
			<pre><code>
			Joe: Hey, do you have that apple?
			:if holding apple
			Joe: Sweet! Bon appetit!
			:else
			Joe: You said you've get me that apple, man!
			:endif
			</pre></code>
	- `inroom`
		- `:if inroom [name of object]`
		- Only true if the room the player is located has that object in it.
		- 	<details>
			<summary><b>Example Usage:</b></summary>
			<pre><code>
			Sweeper Bot: NEED SOMETHING TO SWEEP.
			:if inroom pile of dust
			Sweeper Bot: SWEEPABLE DETECTED. ENGAGE SWEEPING.
			:else
			Sweeper Bot: SLEEP MODE ENGAGED.
			:endif
			</pre></code>
	- `flag` / `flagtrue`
		- `:if flag [name of flag]`
		- `:if flagtrue [name of flag]`
		- Only true if the given flag is true.
			- Flags are global or per-file bools that allow for remembering player choices in branching dialogue.
		- 	<details>
			<summary><b>Example Usage:</b></summary>
			<pre><code>
			You see Joe sitting alone, and walk up to him.
			Joe: Oh hey there, man.
			:if flag gave joe apple
			Joe: Thanks for giving me that apple earlier. It really hit the spot!
			:else
			Joe: I'm starving. Do you have any food?
			:endif
			</pre></code>
	- `flagfalse`
		- `:if flagfalse [name of flag]`
		- Only true if the given flag is false
		- Basically just the opposite of `flag`
		- 	<details>
			<summary><b>Example Usage:</b></summary>
			<pre><code>
			You see Joe sitting alone, and walk up to him.
			Joe: Oh hey there, man.
			:if flagfalse gave joe apple
			Joe: I'm starving. Do you have any food?
			:else
			Joe: Thanks for giving me that apple earlier. It really hit the spot!
			:endif
			</pre></code>
## Branching Dialogue
### :mc
-	`:mc` allows for branching dialogue in a Q/A style with a pre-made options.
-	The first section of the mc block defines the options available to the player.
	-	This section ends with the `:endmcdef` command **(Required)**
	-	<details>
		<summary><b>Example Usage:</b></summary>
		<pre><code>
		Joe: What did you want to ask me?
		:mc
		[1] How did you get here?
		[2] Where are we?
		[3] What's your favourite food?
		:endmcdef
		</pre></code>
- The second section of the mc block begins immediately after `:endmcdef`, and is followed by a series of integer commands denoting the response for the selected option.
- This section ends with `:endmc`, which closes out the mc block **(Required)**
	- <details>
		<summary><b>Example Usage:</b></summary>
		<pre><code>
		Joe: What did you want to ask me?
		:mc
		[1] How did you get here?
		[2] Where are we?
		[3] What's your favourite food?
		[4] I have to go.
		:endmcdef
		1:
		Joe: Me? I boarded the ship on the Nouveau Port just like everyone else aboard.
		:back
		2:
		Joe: We're aboard the Captrualis, the lovely flagship of the Federation!
		:back
		3:
		Joe: My favourite food are apples. I love how sweet and fragrant they are.
		My favourite variety is definitely the Honeycrisp. The texture is to die for!
		:back
		4:
		Joe: I'll see you around, man.
		:continue
		:endmc
		</pre></code>
- You can use any other Command Processor command inside of the mc block too!
	- <details>
		<summary>This allows for nested conditional/branching dialogue as well.</summary>
		<pre><code>
		Joe: What did you want to ask me?
		:mc
		[1] Why are we here?
		:endmcdef
		1:
			Joe: That's a silly question.
			:mc
			[1] Is it really?
			[2] I think it's a perfectly cromulent question.
			:endmcdef
			1:
				Joe: Yeah, it is.
			2:
				Joe: Cromulent isn't a word.
				:if flag cromulent is a word
					Joe: ...Well, I stand corrected.
				:endif
			:endmc
		:endmc
		</pre></code>
- The mc block also supports some additional mc-only commands, such as `:continue` and `:back`.
	- `:continue` tells the Command Processor to finish the mc block.
		- This is usually used as an "exit" from the multiple-choice dialogue.
	- `:back` tells the Command Processor to return to the top of the mc block
		- This allows the player to continue asking questions/responding.

 ## World Interaction
 Commands that allow you to interact with the player, NPCs, and the world.
 ### :move / :movenpc
 - `:move` lets you move the player character to any room on the map.
 - <details>
	<summary><b>Example Usage:</b></summary>
	<pre><code>
	// Moves the player character to the Boiler Room
	:move Boiler Room
	// Moves the player character to the Engine Room
	:move engineroom
	</code></pre>
	</details>
- `:movenpc` lets you move an npc to any room on the map.
	- Due to limitations, the NPC's name must have spaces removed from it.
		- e.g., the NPC named `Captain Ahab` will be `CaptainAhab` when using this command.
	- The Room name does not suffer from this limitation, however.
- <details>
	<summary><b>Example Usage:</b></summary>
	<pre><code>
	// Moves Bob to the Boiler Room
	:movenpc bob boilerroom
	// Moves Captain Ahab to the Engine Room
	:movenpc CaptainAhab Engine Room
	// Moves Barney the Buccaneer to the Boiler Room
	:movenpc barneyTheBuccaneer Boiler Room
	</code></pre>
	</details>
### :give
- `:give` gives the player an object.
- <details>
	<summary><b>Example Usage:</b></summary>
	<pre><code>
	:give apple
	:give orange
	:give pile of rocks
	:give anatomically-correct model of a large alien monkey
	</code></pre>
	</details>
### :block
- `:block` blocks a door in the player's current room for a given reason, preventing traversal in that direction.
	- Use `north/east/south/west` or `n/e/s/w` for directions.
- <details>
	<summary><b>Example Usage:</b></summary>
	<pre><code>
	:block north A large cat is blocking your path.
	:block south Another large cat is in the way.
	:block e What is with all of these large cats?
	</code></pre>
	</details>
### :unblock
- `:unblock` unblocks a door in the player's current room, allowing traversal in that direction.
	- Use `north/east/south/west` or `n/e/s/w` for directions.
- <details>
	<summary><b>Example Usage:</b></summary>
	<pre><code>
	The large cat jumps away!
	:unblock north
	The other large cat flies away!
	:unblock south
	I guess there wasn't a cat blocking this way in the first place...
	:unblock e
	</code></pre>
	</details>

## File Commands
Commands that allow interaction with the file being read, or other files.
### :setflag
- `:setflag` lets you store certain boolean values on a per-file basis.
	- If a flag is set earlier on in the file, it can be read as an `:if` criteria.
- **The last word of the statement has to be `true` or `false`**
- <details>
	<summary><b>Example Usage:</b></summary>
	<pre><code>
	:setflag bunnies are cute true
	:setflag cats are cute true
	:setflag chihuahas are cute false
	:if flag bunnies are cute
		I think so too :)
	:endif
	:if flag chihuahas are cute
		Definitely :)
	:else
		How could you!
		I don't trust your judgement on what is cute anymore! :(
		:setflag bunnies are cute false
		:setflag cats are cute false
	:endif
	</code></pre>
	</details>
### :quit
- `:quit` stops the reading of the current file.
- <details>
	<summary><b>Example Usage:</b></summary>
	<pre><code>
	Some dialogue I want you to see!
	:quit
	This dialogue will never be displayed.
	</code></pre>
	</details>
### :askquit
- `:askquit` prompts the player if they want to continue reading the file or not.
	- Useful for particularly large story elements or dialogue, especially if the information they require was given to them earlier.
- <details>
	<summary><b>Example Usage:</b></summary>
	<pre><code>
	Blah blah
	Here's a code: 1234
	I will now tell you my life story.
	:askquit
	Glad you decided to stick around!
	So once, when I was a child...
	</code></pre>
	</details>
### :pause
- `:pause` Pauses the reading of the file until the player presses Enter.
	- Useful for making large dialogue more readable by breaking it up into chunks.
- <details>
	<summary><b>Example Usage:</b></summary>
	<pre><code>
	Here's a very large section of dialogue talking about some cool stuff.
	This is quite the ramble.
	Very big.
	:pause
	Anyways, as I was saying, this is quite large and hard to read if it were just
	spewed at you in one fell swoop.
	:pause
	It's quite useful to be able to break this up, as it allows for the player
	to have some more control over what they're reading, and at what pace.
	</code></pre>
	</details>
