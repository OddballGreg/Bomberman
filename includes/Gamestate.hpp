/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Gamestate.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghavenga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 20:09:52 by ghavenga          #+#    #+#             */
/*   Updated: 2017/05/26 20:14:43 by ghavenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMESTATE_HPP
# define GAMESTATE_HPP

# include "../includes/Log.hpp"

class Gamestate
{
	public:
		// Constructors & Destructors
		Gamestate();
		Gamestate(const Gamestate &obj);
		~Gamestate();

		// Operators Overloads
		Gamestate& operator =(const Gamestate &obj);

		// Setters
		
		// Member Methods

	private:

};

#endif
