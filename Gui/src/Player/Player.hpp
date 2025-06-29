/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Player.hpp
*/

#ifndef ZAPPY_PLAYER_HPP
    #define ZAPPY_PLAYER_HPP

    #include <tuple>
    #include <mutex>

    #include "Type.hpp"
    #include "Button.hpp"
    #include "AEntity.hpp"
    #include "Inventory.hpp"

namespace gui {
    class Player : public AEntity {
        public:
            Player(int id, std::pair<int, int> position, Orientation orientation, int level, std::string team,
                float scale, int screenWidth, int screenHeight, Camera &camera, CamState &sceneState, std::shared_ptr<int> timeUnit,
                std::shared_ptr<Model> model, Model deadModel, ModelAnimation *animations, int animCount, std::shared_ptr<Model> teamModel);
            ~Player();

            /**
             * @brief Get the team of the Player.
             * This function returns the team of the Player.
             * @return The team of the Player as a string.
             */
            std::string getTeam() const;
            
            /**
             * @brief Get the level of the Player.
             * This function returns the level of the Player.
             * @return The level of the Player as an integer.
             */
            int getLevel() const;

            /**
             * @brief Get the orientation of the Player.
             * This function returns the orientation of the Player.
             * @return The orientation of the Player as an Orientation enum.
             */
            Orientation getOrientation() const;

            /**
             * @brief Get the team of the Player.
             * This function returns the team of the Player.
             * @return The team of the Player as a string.
             */
            int getId() const;

            /**
             * @brief Set the level of the Player.
             * This function sets the level of the Player.
             * @param level The new level of the Player.
             */
            void setLevel(int level);

            /**
             * @brief Set the orientation of the Player.
             * This function sets the orientation of the Player.
             * @param orientation The new orientation of the Player.
             */
            void setOrientation(Orientation orientation);

            /**
             * @brief Draw the Player on the screen.
             * This function draws the Player.
             */
            void draw();

            /**
             * @brief Draw the UI of the Player.
             * This function draws the UI of the Player.
             */
            void drawUI();

            /**
             * @brief Handle the camera button action.
             * This function handles the action when the camera button is clicked.
             */
            void HandleCamButton(Camera &camera, CamState &sceneState);

            /**
             * @brief Update the Player.
             * This function updates the Player's state based on user input.
             * @param camera The Camera3D used for ray picking.
             * @return An integer indicating the result of the update (e.g., success or failure).
             */
            [[nodiscard]] int update(Camera camera);

            /**
             * @brief Update the UI of the Player.
             * This function updates the UI of the Player.
             */
            void updateUI();

            /**
             * @brief Stop the Player from moving.
             * This function stops the Player's movement and resets the animation state.
             */
            void stopMoving();

            /**
             * @brief Set the animation speed of the Player.
             * This function sets the speed at which the Player's animations are played.
             * @param speed The new animation speed.
             */
            void setAnimationSpeed(float speed);

            /**
             * @brief Start moving the Player to a new position.
             * This function initiates the movement of the Player to a specified position.
             * @param newPosition The target position to move the Player to.
             */
            void startMoveTo(Vector3 newPosition);

            /**
             * @brief Check if the Player is selected.
             * This function checks if the Player is currently selected.
             * @return true if the Player is selected, false otherwise.
             */
            bool getSelected() const;

            /**
             * @brief Check if the Player is currently moving.
             * This function checks if the Player is in a moving state.
             * @return true if the Player is moving, false otherwise.
             */
            bool getIsMoving() const;

            /**
             * @brief Set the selected state of the Player.
             * This function sets whether the Player is currently selected.
             * @param isSelected true if the Player is selected, false otherwise.
             */
            void setIncantation(bool incantation);

            /**
             * @brief Set the incantation ended state of the Player.
             * This function sets whether the incantation has ended for the Player.
             * @param incantationEnded true if the incantation has ended, false otherwise.
             */
            void setIncantationEnded(bool incantationEnded);
            
            /**
             * @brief Set the broadcasting state of the Player.
             * This function sets whether the Player is currently broadcasting.
             * @param broadcasting true if the Player is broadcasting, false otherwise.
             */
            void setBroadcasting(bool broadcasting);
            
            /**
             * @brief updateMovementAndAnimation
             * This function updates the Player's movement and animation based on the current state.
             */
            void updateMovementAndAnimation();
            
            /**
             * @brief Handle user input for the Player.
             * This function processes user input to control the Player's actions, such as movement and broadcasting.
             * @param camera The Camera3D used for ray picking.
             * @return An integer indicating the result of the user input handling (e.g., success or failure).
             */
            [[nodiscard]] int handleUserInput(Camera camera);
            
            /**
             * @brief set the dead state of the Player.
             * This function sets whether the Player is dead or not.
             * @param isDead true if the Player is dead, false otherwise.
             */
            void setisDead(bool isDead);

            /**
             * @brief set the inventory of the Player.
             * This function sets the quantity of a specific item in the Player's inventory.
             * @param item The name of the item to set in the inventory.
             * @param quantity The quantity of the item to set in the inventory.
             */
            void setInventory(const std::string item, int quantity);

            /**
             * @brief set the selected state of the Player.
             * This function sets whether the Player is currently selected.
             * @param selected true if the Player is selected, false otherwise.
             */
            void setSelected(bool selected);

            /**
             * @brief Set the color of the Player's team.
             * This function retrieves the color associated with the Player's team.
             * @param color The color to set for the Player's team.
             */
            void setColorTeam(std::shared_ptr<std::map<std::string, Color>> colorTeam);

            /**
             * @brief set the pushed state of the Player.
             * This function sets whether the Player is currently pushed.
             * @param isPushed true if the Player is pushed, false otherwise.
             */
            void setPushed(bool isPushed);

            /**
             * @brief Get the pushed state of the Player.
             * This function retrieves whether the Player is currently pushed.
             * @param isPushed true if the Player is pushed, false otherwise.
             */
            bool getPushed() const;
        private:
            /**
             * @brief Animation of the broadcast.
             * This function handles the animation broadcast for the Player.
             */
            void broadcastAnimation();

            /**
             * @brief Animation of the incantation.
             * This function handles the animation incantation for the Player.
             */
            void IncantationAnimation();

            enum class AnimState {
                IDLE = 0,
                WALKING = 1,
                PICKING = 2,
                BROADCASTING = 3,
                DYING = 4
            };

            /**
             * @brief Set the animation state of the Player.
             * This function sets the current animation state of the Player.
             * @param newState The new animation state to set.
             */
            void setAnimationState(AnimState newState);

            std::shared_ptr<Model> _model;
            std::shared_ptr<int> _timeUnit;


            int _id;
            int _level;
            int _animCount;
            int _currentAnim;
            int _animFrameCounter;
            int _countBeforeExpire = 600;
            
            std::mutex _mutex;
            bool _isMoving;
            bool _isDead = false;
            bool _isPushed = false;
            bool _isSelected = false;
            bool _isIncantation = false;
            bool _isBroadcasting = false;
            bool _isIncantationEnded = false;
            
            std::string _team;

            float _broadcastTimer;
            float _animationSpeed;
            float _broadcastDuration = 0.5f;


            float _IncantationTimer;
            float _IncantationDuration = 2.0f;

            Vector3 _targetPosition;
            
            ui::Button _camButton;
            std::shared_ptr<ui::Inventory> _inventory;

            Model _deadModel; 
            Orientation _direction;
            AnimState _currentAnimState;
            ModelAnimation *_animations;

            int _fontSize;
            std::map<std::string, std::pair<int, Color>> _items;

            Rectangle _bounds;

            std::shared_ptr<Model> _teamModel;

            std::shared_ptr<std::map<std::string, Color>> _colorTeam;
            std::map<int, std::string> _playersNames;
    };
}

#endif //ZAPPY_PLAYER_HPP
